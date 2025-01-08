package main

import (
	"github.com/gin-gonic/gin"
	"net/http"
	"os"
)

func InitRouter() *gin.Engine {
	r := gin.New()
	r.LoadHTMLGlob("amis/template/*")
	r.GET("/index", func(c *gin.Context) {
		//从文件test.json读取json数据
		body, err := os.ReadFile("amis/static/app.json")
		if err != nil {
			c.JSON(http.StatusInternalServerError, gin.H{
				"msg": "读取文件失败",
			})
		}
		c.HTML(200, "home.html", gin.H{
			"App": string(body),
		})
	})
	return r
}
