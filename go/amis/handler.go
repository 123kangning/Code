package main

import (
	"encoding/json"
	"github.com/gin-gonic/gin"
	"net/http"
	"os"
	"path/filepath"
)

type File struct {
	Name string `json:"name"`
	Hash string `json:"hash"`
}

func Index(c *gin.Context) {
	//从文件test.json读取json数据
	body, err := os.ReadFile(schema + "app.json")
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{
			"msg": "读取文件失败",
		})
	}
	c.HTML(200, "home.html", gin.H{
		"App": string(body),
	})
}

func Schema(c *gin.Context) {
	pageKey := c.Query("page_key") + ".json"
	//从文件test.json读取json数据
	body, err := os.ReadFile(schema + pageKey)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{
			"msg": "读取文件失败",
		})
	}
	c.JSON(http.StatusOK, json.RawMessage(body))
}

func Search(c *gin.Context) {
	//返回storage目录下所有文件
	//fmt.Println("进入 search")
	dirs, err := os.ReadDir(root)
	if err != nil {
		c.JSON(200, gin.H{
			"code": -1,
			"msg":  "读取目录失败",
		})
		return
	}
	files := make([]*File, 0)
	for _, dir := range dirs {
		files = append(files, &File{
			Name: dir.Name(),
			Hash: "hash_" + dir.Name(),
		})
	}
	c.JSON(200, gin.H{
		"code": 0,
		"msg":  "success",
		"data": files,
	})
}

func Upload(c *gin.Context) {
	//获取上传的文件
	file, err := c.FormFile("file")
	if err != nil {
		c.JSON(200, gin.H{
			"code": -1,
			"msg":  "上传文件失败",
		})
		return
	}
	//保存文件
	err = c.SaveUploadedFile(file, root+file.Filename)
	if err != nil {
		c.JSON(200, gin.H{
			"code": -1,
			"msg":  "保存文件失败",
		})
		return
	}
	c.JSON(200, gin.H{
		"code": 0,
		"msg":  "success",
	})
}

func DownLoad(c *gin.Context) {
	//读取文件
	file, err := os.Open(root + "test.txt")
	if err != nil {
		c.JSON(200, gin.H{
			"code": -1,
			"msg":  "读取文件失败",
		})
		return
	}
	//defer file.Close()
	//返回文件
	//c.File(file.Name())
	c.Header("Content-Disposition", "attachment")
	c.FileAttachment(file.Name(), filepath.Base(file.Name()))
}
