package mq

import (
	"context"
	"github.com/segmentio/kafka-go"
	"log"
	"testing"
)

func TestSend(t *testing.T) {
	// make a writer that produces to topic-A, using the least-bytes distribution
	w := &kafka.Writer{
		Addr:         kafka.TCP("localhost:9092"),
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
