package main

import (
	"github.com/disintegration/imaging"
	"github.com/golang/freetype"
	"github.com/golang/freetype/truetype"
	"github.com/pkg/errors"
	"golang.org/x/image/font"
	"golang.org/x/image/font/gofont/gomono"
	"image"
	"image/color"
	"image/draw"
)

func AddWatermarkForImage(oriImage image.Image, uid string) (*image.RGBA, error) {
	watermarkedImage := image.NewRGBA(oriImage.Bounds())
	draw.Draw(watermarkedImage, oriImage.Bounds(), oriImage, image.Point{}, draw.Src)

	watermark, err := MakeImageByText(uid, color.Transparent)
	if err != nil {
		return nil, err
	}
	rotatedWatermark := imaging.Rotate(watermark, 30, color.Transparent)

	x, y := 0, 0
	for y <= watermarkedImage.Bounds().Max.Y {
		for x <= watermarkedImage.Bounds().Max.X {
			offset := image.Pt(x, y)
			draw.Draw(watermarkedImage, rotatedWatermark.Bounds().Add(offset), rotatedWatermark, image.Point{}, draw.Over)
			// 稀疏一点, 稍微提升点速度
			x += rotatedWatermark.Bounds().Dx() * 2
		}
		y += rotatedWatermark.Bounds().Dy()
		x = 0
	}
	return watermarkedImage, nil
}

// MakeImageByText 根据文本内容制作一个仅包含该文本内容的图片
func MakeImageByText(text string, bgColor color.Color) (image.Image, error) {
	fontSize := float64(72)
	freetypeCtx := MakeFreetypeCtx(fontSize)

	width, height := int(fontSize)*len(text), int(fontSize)*2
	rgbaRect := image.NewRGBA(image.Rect(0, 0, width, height))

	// 仅当非透明时才做一次额外的渲染
	if bgColor != color.Transparent {
		bgUniform := image.NewUniform(bgColor)
		draw.Draw(rgbaRect, rgbaRect.Bounds(), bgUniform, image.Pt(0, 0), draw.Src)
	}

	freetypeCtx.SetClip(rgbaRect.Rect)
	freetypeCtx.SetDst(rgbaRect)
	pt := freetype.Pt(0, int(freetypeCtx.PointToFixed(fontSize)>>6))
	_, err := freetypeCtx.DrawString(text, pt)
	if err != nil {
		return nil, errors.WithStack(err)
	}
	return rgbaRect, nil
}

// MustParseFont 通过单测来保证该方法必不会 panic
func MustParseFont() *truetype.Font {
	ft, err := freetype.ParseFont(gomono.TTF)
	if err != nil {
		panic(err)
	}
	return ft
}

func MakeFreetypeCtx(fontSize float64) *freetype.Context {
	fontColor := color.RGBA{R: 0, G: 0, B: 0, A: 50}
	fontColorUniform := image.NewUniform(fontColor)

	freetypeCtx := freetype.NewContext()
	freetypeCtx.SetDPI(100)
	freetypeCtx.SetFont(MustParseFont())
	freetypeCtx.SetFontSize(fontSize)
	freetypeCtx.SetSrc(fontColorUniform)
	freetypeCtx.SetHinting(font.HintingNone)
	return freetypeCtx
}
