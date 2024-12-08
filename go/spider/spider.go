package main

import (
	"fmt"
	"github.com/PuerkitoBio/goquery"
	"github.com/chromedp/chromedp"
	"github.com/geziyor/geziyor"
	"github.com/geziyor/geziyor/client"
	"github.com/geziyor/geziyor/export"
)

const (
	cookie    string = `UOR=www.google.com,tousu.sina.com.cn,; SINAGLOBAL=111.203.29.114_1733198147.350357; Apache=111.203.29.114_1733198147.350359; ULV=1733198157354:2:2:2:111.203.29.114_1733198147.350359:1733198147161; U_TRS1=00000072.4efb40863.674e8176.067fb05c; U_TRS2=00000072.4f0440863.674e8176.2e726bd4; SCF=AhWaLNiSLrJdISreXadNAW5CITkPcyGnRyA7VXWvciSAKGjMW5MhvcfDt_Xc34b8Mf_kY9R1NYASZKl21uJ6jGE.; HM-AMT=%7B%22amt%22%3A22470236%2C%22amt24h%22%3A19899%2C%22v%22%3A%222.3.159%22%2C%22vPcJs%22%3A%221.6.73%22%2C%22vPcCss%22%3A%221.2.387%22%7D; SUB=_2A25KSsmyDeRhGeFM6FYS8SnEwjyIHXVpJkN6rDV_PUNbm9AGLUjHkW9NQMKy3JosjbXSK_QycEPKas7JR_3IMmOz; SUBP=0033WrSXqPxfM725Ws9jqgMF55529P9D9W56uAvklg_IpPemXkp0823j5JpX5KzhUgL.FoMEe0B0eKMR1K52dJLoIp7LxKML1KBLBKnLxKqL1hnLBoMNeoeXe02N1h.7; ALF=1735804643`
	useragent string = `Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/131.0.0.0 Safari/537.36`
)

func main() {
	browser := chromedp.Browser{}
	if process := browser.Process(); process != nil {
		fmt.Printf("Browser PID: %v", process.Pid)
	}
	geziyor.NewGeziyor(&geziyor.Options{
		StartRequestsFunc: func(g *geziyor.Geziyor) {
			req, _ := client.NewRequest("GET", "https://tousu.sina.com.cn/index/search/?keywords=%E5%B8%8C%E6%9C%9B%E5%AD%A6&t=1", nil)
			req.Header.Set("Cookie", cookie)
			g.Do(req, g.Opt.ParseFunc)
		},
		ParseFunc: quotesParse,
		Exporters: []export.Exporter{&export.JSON{FileName: "spider/XWX.json"}},
		UserAgent: useragent,
	}).Start()
}
func quotesParse(g *geziyor.Geziyor, r *client.Response) {
	t := r.HTMLDoc.Find("div.main clearfix")
	fmt.Println("t=", t.Text())
	t1 := t.Find("div.blackcat-container")
	fmt.Println("t1=", t1.Text())
	t2 := t1.Find("div.tab-con.tousu-list")
	fmt.Println("t2=", t2.Text())
	t2.Each(func(i int, s *goquery.Selection) {
		e := s.Find("div.black-con")
		g.Exports <- map[string]interface{}{
			"title":   e.Find("h1").Text(),
			"content": s.Find("p").Text(),
		}
	})
	//if href, ok := r.HTMLDoc.Find("li.next > a").Attr("href"); ok {
	//	if url, err := r.Request.URL.Parse(href); err == nil {
	//		g.Get(url.String(), quotesParse)
	//		//g.Get(r.JoinURL(href), quotesParse)
	//	}
	//}
}
