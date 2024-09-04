package main

import (
	"bufio"
	"database/sql"
	"fmt"
	"math"
	"math/rand"
	"os"
	"strconv"
	"strings"
	"time"

	_ "github.com/mattn/go-sqlite3" // 引入 sqlite 驱动
)

/*
GetCounter 方法 返回一个计数器方法，输入 w 重量，返回快递费用
GetWeight 方法 实现了根据权重获取随机重量的方法。
获取以0.1kg为weight单位，可以分为 10*w 个单位,这里w=100。
我们对于每个单位都存储一个浮点数，表示重量小于等于当前值的比例，总的比例我们称为sum。
我们每次会随机选择一个0-sum的随机数，然后通过二分定位到具体的索引单位，每个索引单位表示0.1kg,
通过索引单位我们可以得到最终的随机重量。
*/
const (
	maxWeight   = 100
	totalUsers  = 1000
	totalOrders = 100000
)

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

func GetWeight(w int) func() float64 {
	var sum float64 = 0
	nums := make([]float64, 10*w+1)
	for i := 1; i <= w*10; i++ {
		cur := float64(1) / (float64(i) / 10)
		nums[i] = cur + nums[i-1]
		sum += cur
	}
	return func() float64 {
		randomValue := rand.Float64() * sum
		left, right := 0, 10*w
		for left < right {
			mid := left + (right-left)/2
			if nums[mid] >= randomValue {
				right = mid
			} else {
				left = mid + 1
			}
		}
		return float64(left) / 10
	}

}

func generateRandomOrder(weighter func() float64) Order {
	userID := rand.Intn(totalUsers) + 1
	weight := weighter()
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
	db := createSQLiteDB("identifier.sqlite")
	defer db.Close()
	initDB(db)
	weighter := GetWeight(maxWeight)

	reader := bufio.NewReader(os.Stdin)
	sign := ""
	for sign != "quic" {
		fmt.Printf("=====================" +
			"\ninit：初始化10万条订单\nq uid：查询指定用户订单\nc：退出\n" +
			"=====================\n")
		line, _ := reader.ReadString('\n')
		part := strings.Fields(line)
		sign = part[0]
		switch sign {
		case "init":
			{
				fmt.Println("orders初始化中...")
				var orders []Order
				for i := 0; i < totalOrders/10; i++ {
					order := generateRandomOrder(weighter)
					orders = append(orders, order)
					if err := insertOrder(db, order); err != nil {
						fmt.Printf("Error inserting order: %v\n", err)
					}
				}
				fmt.Println("orders初始化完成")
			}
		case "q":
			{
				// 查询功能示例
				uid, err := strconv.Atoi(part[1])
				if err != nil {
					fmt.Println("uid输入不规范")
					break
				}
				queryUserOrders(db, uid)
			}
		case "c":
			return
		}
	}

}

// GetCounter 返回一个计数器方法，输入 w 重量，返回快递费用
func GetCounter() func(w float64) int {
	w2Cost := make(map[int]int, 100)
	base := 18
	lastLevel := base
	w2Cost[1] = 18
	for i := 2; i <= 100; i++ {
		cur := int(math.Round(float64((i-1)*5+base) + float64(lastLevel)*0.01))
		lastLevel = cur
		w2Cost[i] = cur
	}
	return func(w float64) int {
		realW := int(math.Ceil(w))
		return w2Cost[realW]
	}
}

func queryUserOrders(db *sql.DB, userID int) {
	rows, err := db.Query("SELECT id, weight FROM orders WHERE uid=?", userID)
	if err != nil {
		fmt.Printf("Query failed: %v\n", err)
		return
	}
	defer rows.Close()

	var totalCost int
	counter := GetCounter()
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
