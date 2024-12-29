package mq

import (
	"context"
	"fmt"
	"github.com/segmentio/kafka-go"
	"log"
	"testing"
	"time"
)

func TestRead(t *testing.T) {
	// make a new reader that consumes from topic-A
	r := kafka.NewReader(kafka.ReaderConfig{
		Brokers:  []string{"localhost:9092"},
		GroupID:  "order",
		Topic:    "topic-A",
		MaxBytes: 10e6, // 10MB
	})

	defer func() {
		if err := r.Close(); err != nil {
			log.Fatal("failed to close reader:", err)
		}
	}()
	ctx := context.Background()
	for {
		m, err := r.FetchMessage(ctx)
		if err != nil {
			break
		}
		fmt.Printf("%v message at topic/partition/offset %v/%v/%v: %s = %s\n", time.Now(), m.Topic, m.Partition, m.Offset, string(m.Key), string(m.Value))
		if err := r.CommitMessages(ctx, m); err != nil {
			log.Fatal("failed to commit messages:", err)
		}
	}
}
