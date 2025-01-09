package main

import (
	"image"
	"image/color"
	"image/draw"
	"image/jpeg"
	"image/png"
	"os"
	"testing"

	"github.com/stretchr/testify/assert"
)

//https://www.cnblogs.com/XiaoXiaoShuai-/p/17054080.html
func TestMakeImageByText(t *testing.T) {
	t.Run("bg white", func(t *testing.T) {
		img, err := MakeImageByText("hello", color.White)
		assert.NoError(t, err)

		helloPng, err := os.Create("static/hello_white.png")
		assert.NoError(t, err)
		defer helloPng.Close()

		err = png.Encode(helloPng, img)
		assert.NoError(t, err)

		helloJpeg, err := os.Create("static/hello_white.jpeg")
		assert.NoError(t, err)
		defer helloJpeg.Close()

		err = jpeg.Encode(helloJpeg, img, nil)
		assert.NoError(t, err)
	})
	t.Run("bg transparent", func(t *testing.T) {
		img, err := MakeImageByText("hello", color.Transparent)
		assert.NoError(t, err)

		helloPng, err := os.Create("static/hello_transparent.png")
		assert.NoError(t, err)
		defer helloPng.Close()

		err = png.Encode(helloPng, img)
		assert.NoError(t, err)

		helloJpeg, err := os.Create("static/hello_transparent.jpeg")
		assert.NoError(t, err)
		defer helloJpeg.Close()

		// jpeg 没有 alpha 通道, 所以会是全黑的
		err = jpeg.Encode(helloJpeg, img, nil)
		assert.NoError(t, err)
	})
}

func TestMustParseFont(t *testing.T) {
	ft := MustParseFont()
	assert.NotNil(t, ft)
}

func BaseImageForTest() image.Image {
	rgbaRect := image.NewRGBA(image.Rect(0, 0, 3000, 2000))
	bgColor := color.RGBA{R: 0xff, G: 0, B: 0, A: 0xff}
	bg := image.NewUniform(bgColor)
	draw.Draw(rgbaRect, rgbaRect.Bounds(), bg, image.Pt(0, 0), draw.Src)
	return rgbaRect
}

func TestWassObject_AddWatermark(t *testing.T) {
	baseImg := BaseImageForTest()

	watermarkedImg, err := AddWatermarkForImage(baseImg, "hello.world")
	assert.NoError(t, err)

	helloWatermarkedJpeg, err := os.Create("static/hello_watermarked.jpeg")
	assert.NoError(t, err)
	defer helloWatermarkedJpeg.Close()

	err = jpeg.Encode(helloWatermarkedJpeg, watermarkedImg, nil)
	assert.NoError(t, err)
}
