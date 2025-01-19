package mq

import (
	"context"
	"github.com/segmentio/kafka-go"
	"log"
	"testing"
	"time"
)

func BenchmarkSendMessage(b *testing.B) {
	b.Run("基于Conn发送消息", func(b *testing.B) {
		conn, err := getConn()
		if err != nil {
			log.Fatal("failed to dial leader:", err)
		}
		// 关闭连接
		if err := conn.Close(); err != nil {
			log.Fatal("failed to close writer:", err)
		}
		for i := 0; i < b.N; i++ {
			WriteByConn(conn)
		}
	})
	b.Run("不复用writer", func(b *testing.B) {
		for i := 0; i < b.N; i++ {
			SendMessage()
		}
	})
	b.Run("复用writer", func(b *testing.B) {
		w := getWriter()
		defer func() {
			if err := w.Close(); err != nil {
				log.Fatal("failed to close writer:", err)
			}
		}()
		for i := 0; i < b.N; i++ {
			SendMessage2(w)
		}
	})

}

func TestSend(t *testing.T) {
	// make a writer that produces to topic-A, using the least-bytes distribution
	SendMessage()
}

func SendMessage2(w *kafka.Writer) {
	write(w)
}

func SendMessage() {
	w := getWriter()
	defer func() {
		if err := w.Close(); err != nil {
			log.Fatal("failed to close writer:", err)
		}
	}()

	write(w)
}

func getWriter() *kafka.Writer {
	w := &kafka.Writer{
		Addr:                   kafka.TCP("localhost:9091", "localhost:9092", "localhost:9093"),
		Topic:                  "topic-A",
		Balancer:               &kafka.LeastBytes{}, //Hash, RoundRobin, LeastBytes
		RequiredAcks:           kafka.RequireOne,    //Leader写入成功即可
		AllowAutoTopicCreation: true,
	}
	return w
}

func write(w *kafka.Writer) {
	err := w.WriteMessages(context.Background(),
		kafka.Message{
			Key:   []byte("Key-A"),
			Value: []byte("nero!"),
		},
		kafka.Message{
			Key:   []byte("Key-B"),
			Value: []byte("One!"),
		},
		kafka.Message{
			Key:   []byte("Key-C"),
			Value: []byte("Two!"),
		},
	)
	if err != nil {
		log.Fatal("failed to write messages:", err)
	}
}

func TestWrite(t *testing.T) {
	conn, err := getConn()
	if err != nil {
		log.Fatal("failed to dial leader:", err)
	}
	WriteByConn(conn)
}

// WriteByConn 基于Conn发送消息
func WriteByConn(conn *kafka.Conn) {

	// 发送消息
	_, err := conn.WriteMessages(
		kafka.Message{Value: []byte("one!")},
		kafka.Message{Value: []byte("two!")},
		kafka.Message{Value: []byte("three!")},
	)
	if err != nil {
		log.Fatal("failed to write messages:", err)
	}
}

func getConn() (*kafka.Conn, error) {
	w := getWriter()

	// 连接至Kafka集群的Leader节点
	conn, err := kafka.DialLeader(context.Background(), w.Addr.Network(), w.Addr.String(), w.Topic, 0)
	if err != nil {
		log.Fatal("failed to dial leader:", err)
	}

	// 设置发送消息的超时时间
	conn.SetWriteDeadline(time.Now().Add(10 * time.Second))
	return conn, err
}
