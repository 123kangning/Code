package main

import (
	"database/sql"
	"fmt"
	"math/rand"
	"test/temp"
	"time"

	_ "github.com/mattn/go-sqlite3" // 引入 sqlite 驱动
)

const (
	maxWeight   = 100
	totalUsers  = 1000
	totalOrders = 100000
)

var weights = []int{2, 4, 6, 8} // 假设只有这几种权重的订单

type Order struct {
	ID        int
	UserID    int
	Weight    float64
	CreatedAt time.Time
}

func createSQLiteDB(dbName string) *sql.DB {
	db, err := sql.Open("sqlite3", dbName)
	if err != nil {
		panic(err)
	}
	return db
}

func initDB(db *sql.DB) {
	_, err := db.Exec(`CREATE TABLE IF NOT EXISTS orders (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        uid INTEGER,
        weight DOUBLE,
        created_at DATETIME DEFAULT CURRENT_TIMESTAMP
    )`)
	if err != nil {
		panic(err)
	}
}

func GetWeight(w int) func() int {
	var sum float64 = 0
	nums := make([]float64, w+1)
	for i := 1; i <= w; i++ {
		cur := float64(1) / float64(i)
		nums[i] = cur
		sum += cur
	}
	return func() int {
		randomValue := rand.Float64() * sum
		left, right := 0, w
		for left < right {
			mid := left + (right-left)/2
			if nums[mid] >= randomValue {
				right = mid
			} else {
				left = mid + 1
			}
		}
		return left
	}

}

func generateRandomOrder(weighter func() int) Order {
	userID := rand.Intn(totalUsers) + 1
	weight := float64(weighter())
	createdAt := time.Now()
	return Order{
		UserID:    userID,
		Weight:    weight,
		CreatedAt: createdAt,
	}
}

func insertOrder(db *sql.DB, order Order) error {
	stmt, err := db.Prepare("INSERT INTO orders(uid, weight) VALUES (?, ?)")
	if err != nil {
		return err
	}
	defer stmt.Close()

	_, err = stmt.Exec(order.UserID, order.Weight)
	return err
}

func main() {
	db := createSQLiteDB("orders.db")
	defer db.Close()

	initDB(db)
	weighter := GetWeight(maxWeight)
	var orders []Order
	for i := 0; i < totalOrders; i++ {
		order := generateRandomOrder(weighter)
		orders = append(orders, order)
		if err := insertOrder(db, order); err != nil {
			fmt.Printf("Error inserting order: %v\n", err)
		}
	}

	// 查询功能示例
	queryUserOrders(db, 100) // 查询用户ID为100的所有订单及总费用
}

func queryUserOrders(db *sql.DB, userID int) {
	rows, err := db.Query("SELECT id, weight FROM orders WHERE uid=?", userID)
	if err != nil {
		fmt.Printf("Query failed: %v\n", err)
		return
	}
	defer rows.Close()

	var totalCost int
	counter := temp.GetCounter()
	for rows.Next() {
		var orderID int
		var weight float64
		if err := rows.Scan(&orderID, &weight); err != nil {
			fmt.Printf("Scan failed: %v\n", err)
			continue
		}
		cost := counter(weight)
		totalCost += cost
		fmt.Printf("Order ID: %d, Weight: %.2fKG, Cost: %d\n", orderID, weight, cost)
	}

	if err := rows.Err(); err != nil {
		fmt.Printf("Rows iteration failed: %v\n", err)
	}

	fmt.Printf("Total cost for user %d: %d\n", userID, totalCost)
}
