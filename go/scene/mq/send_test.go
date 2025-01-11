package mq

import (
	"context"
	"github.com/segmentio/kafka-go"
	"log"
	"testing"
	"time"
)

func TestSend(t *testing.T) {
	// make a writer that produces to topic-A, using the least-bytes distribution
	w := &kafka.Writer{
		Addr:         kafka.TCP("localhost:9091", "localhost:9092", "localhost:9093"),
		Topic:        "topic-A",
		Balancer:     &kafka.LeastBytes{}, //Hash, RoundRobin, LeastBytes
		RequiredAcks: kafka.RequireOne,    //Leader写入成功即可
	}
	defer func() {
		if err := w.Close(); err != nil {
			log.Fatal("failed to close writer:", err)
		}
	}()

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
	WriteByConn()
}

// WriteByConn 基于Conn发送消息
func WriteByConn() {
	topic := "topic-A"
	partition := 0

	// 连接至Kafka集群的Leader节点
	conn, err := kafka.DialLeader(context.Background(), "tcp", "172.17.0.1:9091", topic, partition)
	if err != nil {
		log.Fatal("failed to dial leader:", err)
	}

	// 设置发送消息的超时时间
	conn.SetWriteDeadline(time.Now().Add(10 * time.Second))

	// 发送消息
	_, err = conn.WriteMessages(
		kafka.Message{Value: []byte("one!")},
		kafka.Message{Value: []byte("two!")},
		kafka.Message{Value: []byte("three!")},
	)
	if err != nil {
		log.Fatal("failed to write messages:", err)
	}

	// 关闭连接
	if err := conn.Close(); err != nil {
		log.Fatal("failed to close writer:", err)
	}
}
