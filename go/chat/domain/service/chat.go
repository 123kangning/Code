package service

//type chatService struct{}
//
//// GetMessage 流式发送
//func (c *chatService) GetMessage(ctx *gin.Context) {
//
//	t := time.NewTicker(time.Millisecond * 100)
//	count := 0
//
//	ctx.Header("Content-Type", "text/event-stream")
//	for range t.C {
//		count++
//		ctx.Stream(func(w io.Writer) bool {
//			buf := bufio.NewWriter(w)
//			_, err := buf.WriteString(fmt.Sprintln("data-", count))
//			if err != nil {
//				xlog.Error(ctx.Request.Context(), fmt.Sprintf("ChapterList write fail, httpReq: %+v , err %+v", ctx.Request, err))
//			}
//			err = buf.Flush()
//			if err != nil {
//				return true
//			}
//			return false
//		})
//		if count == 100 {
//			break
//		}
//	}
//	return
//}
