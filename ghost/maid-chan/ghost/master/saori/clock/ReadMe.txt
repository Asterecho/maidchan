AnalogClock.dll Readme
    by Pygmalion

-------------------------------------------------------------------------------
功能:
 AnalogClock.dll为时钟控件的SAORI。

关数:
第一关数:
 show:
  显示时钟。

   第二关数:
      入口名

第一关数:
 hide:
  隐藏时钟。

事件:
OnClockTime
  reference0 小时
  reference1 分钟
  reference2 秒

使用方法:
 以橘花为例,先将AnalogClock.dll,clock.txt和背景图放入saori下。


 AYA:
 在aya_mouse.dic的适当的地方加入

  _result=FUNCTIONEX("saori\AnalogClock.dll","show","clock")

  OnClockTime
 {
	"\0\s[0]现在是%(reference0):%(reference1):%(reference2)\e"
 }


clock.txt的规格书:

[rclock]//入口名
background.image,rbg.png //背景图
//时钟中心位置
centre.x,57
centre.y,57

dot.r,2	//时钟轴心的半径
dot.color,0x808080//时钟轴心的颜色

hour.width,5//时针宽度
hour.length,30//时针长度
hour.color,0x808080//时针颜色

minute.width,2//分针宽度
minute.length,40//分针长度
minute.color,0xc0c0c0//分针颜色

second.width,1//秒针宽度
second.length,40 //秒针长度
second.color,0xe60000 //秒针颜色

[clock]//入口名
background.image,7c_face1.png //背景图
//时钟中心位置
centre.x,90
centre.y,90

dot.image,7c_ring1.png//时钟轴心的图片
//时钟轴心位于时钟轴心图片中的位置
dot.x,90
dot.y,90

hour.image,7c_hour1.png//时针的图片
//时钟轴心位于时针图片中的位置
hour.x,90
hour.y,90

minute.image,7c_minute1.png//分针的图片
//时钟轴心位于分针图片中的位置
minute.x,90
minute.y,90

second.image,7c_second1.png//秒针的图片
//时钟轴心位于秒针图片中的位置
second.x,90
second.y,90

规格书中不同指针可用贴图和画线不同方法绘制.
如:
[rclock]
background.image,7c_face1.png 
centre.x,90
centre.y,90

dot.image,7c_ring1.png
dot.x,90
dot.y,90

hour.width,5
hour.length,30
hour.color,0x808080

minute.width,2
minute.length,40
minute.color,0xc0c0c0

second.image,7c_second1.png
second.x,90
second.y,90



履历:
2008/6/21 1.2版发布.
	修正png图片的Alpha通道支持,改变了规格书的条目,添加用户设定保存.
2008/6/17 1.1Beta版发布.
	修正指针大小设定,去除原有的刻度和数字.
2008/6/14 1.0版发布.
