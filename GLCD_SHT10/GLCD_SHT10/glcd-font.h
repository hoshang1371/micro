﻿#ifndef GLCD_FONT_H_
#define GLCD_FONT_H_
char Sys5x7[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, //32/ --> (space)
    0x00, 0x4F, 0x00, 0x00, 0x00, //33/ --> !
    0x07, 0x00, 0x07, 0x00, 0x00, //34/ --> "
    0x14, 0x7F, 0x14, 0x7F, 0x14, //35/ --> #
    0x24, 0x2A, 0x7F, 0x2A, 0x12, //36/ --> $
    0x23, 0x13, 0x08, 0x64, 0x62, //37/ --> %
    0x36, 0x49, 0x55, 0x22, 0x40, //38/ --> &
    0x00, 0x05, 0x03, 0x00, 0x00, //39/ --> '
    0x1C, 0x22, 0x41, 0x00, 0x00, //40/ --> (
    0x41, 0x22, 0x1C, 0x00, 0x00, //41/ --> )
    0x14, 0x08, 0x3E, 0x08, 0x14, //42/ --> *
    0x08, 0x08, 0x3E, 0x08, 0x08, //43/ --> +
    0x00, 0x28, 0x18, 0x00, 0x00, //44/ --> ,
    0x08, 0x08, 0x08, 0x08, 0x08, //45/ --> -
    0x30, 0x30, 0x00, 0x00, 0x00, //46/ --> .
    0x20, 0x10, 0x08, 0x04, 0x02, //47/ --> /
    0x00, 0x30, 0x48, 0x48, 0x30, //48/ --> 0 0x3E, 0x51, 0x49, 0x45, 0x3E,
    0x00, 0x00, 0x00, 0x00, 0x7E,//49/ --> 1 0x00, 0x42, 0x7F, 0x40, 0x00,
    0x00, 0x7E, 0x08, 0x08, 0x06, //50/ --> 2 0x42, 0x61, 0x51, 0x49, 0x46,
    0x7E, 0x08, 0x06, 0x08, 0x06, //51/ --> 3	0x21, 0x41, 0x45, 0x4B, 0x31, 
    0x7C, 0x10, 0x1C, 0x12, 0x12, //52/ --> 4	0x18, 0x14, 0x12, 0x7F, 0x10,
    0x30, 0x4A, 0x24, 0x48, 0x30, //53/ --> 5	0x27, 0x45, 0x45, 0x45, 0x39,
    0x00, 0x4C, 0x32, 0x10, 0x08,  //54/ --> 6	0x3C, 0x4A, 0x49, 0x49, 0x30,  0x26, 0x19, 0x08, 0x04, 0x00,
    0x06, 0x18, 0x60, 0x18, 0x06, //55/ --> 7	0x01, 0x71, 0x09, 0x05, 0x03,
    0x60, 0x18, 0x06, 0x18, 0x60, //56/ --> 8	0x36, 0x49, 0x49, 0x49, 0x36,
    0x00, 0x0C, 0x12, 0x12, 0x7C , //57/ --> 9	0x06, 0x49, 0x49, 0x29, 0x1E,  
    0x00, 0x36, 0x36, 0x00, 0x00, //58/ --> :
    0x00, 0x56, 0x36, 0x00, 0x00, //59/ --> ;
    0x08, 0x14, 0x22, 0x41, 0x00, //60/ --> <
    0x24, 0x24, 0x24, 0x24, 0x24, //61/ --> =
    0x00, 0x41, 0x22, 0x14, 0x08, //62/ --> >
    0x02, 0x01, 0x51, 0x09, 0x06, //63/ --> ?
    0x32, 0x49, 0x79, 0x41, 0x3E, //64/ --> @
    0x7E, 0x11, 0x11, 0x11, 0x7E, //65/ --> A
    0x7F, 0x49, 0x49, 0x49, 0x36, //66/ --> B
    0x3E, 0x41, 0x41, 0x41, 0x22, //67/ --> C
    0x7F, 0x41, 0x41, 0x22, 0x1C, //68/ --> D
    0x7F, 0x49, 0x49, 0x49, 0x41, //69/ --> E
    0x7F, 0x09, 0x09, 0x09, 0x01, //70/ --> F
    0x3E, 0x41, 0x49, 0x49, 0x3A, //71/ --> G
    0x7F, 0x08, 0x08, 0x08, 0x7F, //72/ --> H
    0x00, 0x41, 0x7F, 0x41, 0x00, //73/ --> I
    0x20, 0x40, 0x41, 0x3F, 0x01, //74/ --> J
    0x7F, 0x08, 0x14, 0x22, 0x41, //75/ --> K
    0x7F, 0x40, 0x40, 0x40, 0x40, //76/ --> L
    0x7F, 0x02, 0x0C, 0x02, 0x7F, //77/ --> M
    0x7F, 0x04, 0x08, 0x10, 0x7F, //78/ --> N
    0x3E, 0x41, 0x41, 0x41, 0x3E, //79/ --> O
    0x7F, 0x09, 0x09, 0x09, 0x06, //80/ --> P
    0x3E, 0x41, 0x51, 0x21, 0x5E, //81/ --> Q
    0x7F, 0x09, 0x19, 0x29, 0x46, //82/ --> R
    0x46, 0x49, 0x49, 0x49, 0x31, //83/ --> S
    0x01, 0x01, 0x7F, 0x01, 0x01, //84/ --> T
    0x3F, 0x40, 0x40, 0x40, 0x3F, //85/ --> U
    0x1F, 0x20, 0x40, 0x20, 0x1F, //86/ --> V
    0x3F, 0x40, 0x60, 0x40, 0x3F, //87/ --> W
    0x63, 0x14, 0x08, 0x14, 0x63, //88/ --> X
    0x07, 0x08, 0x70, 0x08, 0x07, //89/ --> Y
    0x61, 0x51, 0x49, 0x45, 0x43, //90/ --> Z
    0x7F, 0x41, 0x41, 0x00, 0x00, //91/ --> [
    0x15, 0x16, 0x7C, 0x16, 0x15, //92/ --> '\'
    0x41, 0x41, 0x7F, 0x00, 0x00, //93/ --> ]
    0x04, 0x02, 0x01, 0x02, 0x04, //94/ --> ^
    0x40, 0x40, 0x40, 0x40, 0x40, //95/ --> _
    0x01, 0x02, 0x04, 0x00, 0x00, //96/ --> `
    0x20, 0x54, 0x54, 0x54, 0x78, //97/ --> a
    0x7F, 0x44, 0x44, 0x44, 0x38, //98/ --> b
    0x38, 0x44, 0x44, 0x44, 0x00, //99/ --> c
    0x38, 0x44, 0x44, 0x48, 0x7F, //100/ --> d
    0x38, 0x54, 0x54, 0x54, 0x18, //101/ --> e
    0x10, 0x7E, 0x11, 0x01, 0x02, //102/ --> f
    0x0C, 0x52, 0x52, 0x52, 0x3E, //103/ --> g
    0x7F, 0x08, 0x04, 0x04, 0x78, //104/ --> h
    0x00, 0x44, 0x7D, 0x40, 0x00, //105/ --> i
    0x20, 0x40, 0x40, 0x3D, 0x00, //106/ --> j
    0x7F, 0x10, 0x28, 0x44, 0x00, //107/ --> k
    0x00, 0x41, 0x7F, 0x40, 0x00, //108/ --> l
    0x7C, 0x04, 0x18, 0x04, 0x78, //109/ --> m
    0x7C, 0x08, 0x04, 0x04, 0x78, //110/ --> n
    0x38, 0x44, 0x44, 0x44, 0x38, //111/ --> o
    0x7C, 0x14, 0x14, 0x14, 0x08, //112/ --> p
    0x08, 0x14, 0x14, 0x18, 0x7C, //113/ --> q
    0x7C, 0x08, 0x04, 0x04, 0x08, //114/ --> r
    0x48, 0x54, 0x54, 0x54, 0x20, //115/ --> s
    0x04, 0x3F, 0x44, 0x40, 0x20, //116/ --> t
    0x3C, 0x40, 0x40, 0x20, 0x7C, //117/ --> u
    0x1C, 0x20, 0x40, 0x20, 0x1C, //118/ --> v
    0x1E, 0x20, 0x10, 0x20, 0x1E, //119/ --> w
    0x22, 0x14, 0x08, 0x14, 0x22, //120/ --> x
    0x06, 0x48, 0x48, 0x48, 0x3E, //121/ --> y
    0x44, 0x64, 0x54, 0x4C, 0x44, //122/ --> z
    0x08, 0x36, 0x41, 0x00, 0x00, //123/ --> {
	0x00, 0x00, 0x7F, 0x00, 0x00, //124/ --> |
    0x41, 0x36, 0x08, 0x00, 0x00, //125/ --> }
    0x08, 0x08, 0x2A, 0x1C, 0x08, //126/ --> ~
//     0x08, 0x1C, 0x2A, 0x08, 0x08, //127/ --> /113/ --> q
// 0x00,0x7C,0x08,0x04,0x04,0x08,0x00,0x00, //114/ --> r
// 0x00,0x48,0x54,0x54,0x54,0x20,0x00,0x00, //115/ --> s
// 0x00,0x04,0x3F,0x44,0x40,0x20,0x00,0x00, //116/ --> t
// 0x00,0x3C,0x40,0x40,0x20,0x7C,0x00,0x00, //117/ --> u
// 0x00,0x1C,0x20,0x40,0x20,0x1C,0x00,0x00, //118/ --> v
// 0x00,0x1E,0x20,0x10,0x20,0x1E,0x00,0x00, //119/ --> w
// 0x00,0x22,0x14,0x08,0x14,0x22,0x00,0x00, //120/ --> x
// 0x00,0x06,0x48,0x48,0x48,0x3E,0x00,0x00, //121/ --> y
// 0x00,0x44,0x64,0x54,0x4C,0x44,0x00,0x00, //122/ --> z
// 0x00,0x08,0x36,0x41,0x00,0x00,0x00,0x00, //123/ --> {
// 	0x00,0x00,0x00,0x7F,0x00,0x00,0x00,0x00, //124/ --> |
// 0x00,0x41,0x36,0x08,0x00,0x00,0x00,0x00, //125/ --> }
// 0x00,0x08,0x08,0x2A,0x1C,0x08,0x00,0x00, //126/ --> ~
// 0x00,0x08,0x1C,0x2A,0x08,0x08,0x00,0x00, //127/ --> 
};
char SysFarsi5x7[] = {
0x00,0x08,0x1C,0x2A,0x08,0x08,0x00,0x00, //127/ --> 
0x00,0x3C,0x42,0x41,0x42,0x3C,0x00,0x00, //128/ --> 5 فارسی
0x00,0x30,0x28,0x60,0xA0,0x60,0x28,0x30, //129/ --> پ
0x20,0x20,0x20,0x20,0xA0,0x20,0x28,0x30, //130/ --> ب اول
0x20,0x20,0x20,0x20,0xB0,0x20,0x20,0x20, //131/ --> ب اول و اخر
0x00,0x30,0x28,0x20,0xA0,0x20,0x30,0x20, //132/ --> ب اخر
0x20,0x20,0x20,0x22,0x20,0x22,0x28,0x30, //133/ --> ت اول
0x20,0x20,0x20,0x22,0x30,0x22,0x20,0x20, //134/ --> ت اول و اخر
0x00,0x30,0x28,0x22,0x20,0x22,0x30,0x20, //135/ --> ت اخر
0x20,0x20,0x20,0x22,0x21,0x22,0x28,0x30, //136/ --> ث اول
0x20,0x20,0x20,0x22,0x31,0x22,0x20,0x20, //137/ --> ث اول و اخر
0x00,0x30,0x28,0x22,0x21,0x22,0x30,0x20, //138/ --> ث اخر
0x20,0x20,0x28,0x28,0x28,0xB0,0x20,0x20, //139/ --> ج چسبان
0x20,0x20,0x28,0x28,0x28,0x30,0x20,0x20, //140/ -->  اول و اخرح چسبان
0x00,0xC0,0xA8,0x28,0x68,0xB0,0x60,0x20, //141/ --> چ
0x00,0x00,0x80,0x80,0x44,0x32,0x04,0x00, //142/ --> ژ  1
0x00,0x24,0x25,0x24,0x38,0x20,0x20,0x20, //143/ --> خ اول و اخر  2
0x30,0x24,0x22,0x21,0x24,0x2A,0x11,0x00, //144/ --> گ  3
0x00,0x80,0x80,0x40,0x34,0x20,0x20,0x20, //145/ --> ز چسبان  4
0x20,0x20,0x20,0x38,0x20,0x38,0x20,0x18, //146/ --> س اول  5
0x20,0x20,0x38,0x20,0x38,0x20,0x38,0x20, //147/ --> س اول و اخر  6
0x60,0x80,0x80,0x78,0x20,0x38,0x20,0x18, //148/ --> س اخر  7
0x20,0x20,0x20,0x38,0x22,0x39,0x22,0x18, //149/ -->  شبیه ش  8
0x20,0x20,0x38,0x22,0x39,0x22,0x38,0x20, //150/ --> ش اول و اخر  9
0x60,0x80,0x80,0x78,0x22,0x39,0x22,0x18, //151/ --> ش اخر  10
0x30,0x20,0x20,0x20,0x24,0x2A,0x11,0x00, //152/ --> ک  11
0x20,0x30,0x20,0x30,0x28,0x28,0x38,0x20, //153/ --> ص اول  12
0x60,0x80,0x80,0x60,0x30,0x28,0x28,0x38, //154/ --> ص اخر  13
0x20,0x20,0x30,0x20,0x30,0x28,0x2A,0x18, //155/ --> ض اول  14
0x20,0x30,0x20,0x30,0x28,0x2A,0x38,0x20, //156/ --> ض اول و اخر  15
0x60,0x80,0x80,0x60,0x30,0x28,0x2A,0x38, //157/ --> ض اخر  16
0x20,0x20,0x3E,0x30,0x28,0x28,0x38,0x20, //158/ --> ط چسبان  17
0x20,0x20,0x3E,0x30,0x28,0x2A,0x38,0x20, //159/ --> ظ چسبان  18
0x20,0x20,0x20,0x20,0x30,0x28,0x28,0x00, //160/ --> ع اول  19
0x20,0x20,0x20,0x30,0x28,0x28,0x20,0x20, //161/ --> ع اخر اول 20
0x00,0x40,0xA0,0xB0,0x28,0x28,0x20,0x20, //162/ --> 21 ع اخر
0x20,0x20,0x20,0x20,0x30,0x28,0x2A,0x00, //163/ --> غ اول
0x20,0x20,0x20,0x30,0x28,0x2A,0x20,0x20, //164/ --> غ اول و اخر
0x00,0x40,0xA0,0xB0,0x28,0x2A,0x20,0x20, //165/ --> غ اخر
0x20,0x20,0x20,0x20,0x30,0x28,0x2A,0x30, //166/ --> ف اول
0x20,0x20,0x30,0x28,0x2A,0x30,0x20,0x20, //167/ -->  ف اول و اخر
0x00,0x18,0x20,0x20,0x30,0x28,0x2A,0x30, //168/ --> ف اخز
0x20,0x20,0x20,0x20,0x30,0x2A,0x28,0x32, //169/ --> ق اول
0x20,0x20,0x30,0x2A,0x28,0x32,0x20,0x20, //170/ --> ق اول و اخر
0x60,0x80,0x80,0xB2,0xA8,0x7A,0x20,0x20, //171/ --> ق اخر
0x22,0x25,0x25,0x25,0x25,0x25,0x25,0x19, //172/ --> ک اول
0x20,0x20,0x20,0x1C,0x22,0x21,0x20,0x20, //173/ --> ک اول و اخر
0x30,0x28,0x2C,0x2A,0x20,0x3F,0x20,0x20, //174/ --> ک اخر
0x20,0x20,0x20,0x20,0x20,0x20,0x1F,0x00, //175/ --> ل اول
0x20,0x20,0x20,0x20,0x1F,0x20,0x20,0x20, //176/ --> ل اول واخر
0x00,0x30,0x40,0x40,0x3F,0x20,0x20,0x20, //177/ --> ل اخر
0x20,0x20,0x20,0x20,0x30,0x48,0x48,0x30, //178/ --> م اول
0x20,0x20,0x30,0x48,0x48,0x30,0x20,0x20, //179/ --> م وسط
0x80,0x40,0x30,0x48,0x48,0x30,0x20,0x20, //180/ --> م اخر
0x20,0x20,0x20,0x20,0x22,0x20,0x18,0x00, //181/ --> ن اول
0x20,0x20,0x20,0x20,0x1A,0x20,0x20,0x20, //182/ --> ن وسط
0x30,0x40,0x44,0x40,0x30,0x20,0x20,0x20, //183/ --> ن اخر
0x20,0x20,0x20,0x30,0x28,0x3A,0x2C,0x18, //184/ --> ه اول
0x20,0x20,0x30,0x28,0x3A,0x2C,0x38,0x20, //185/ --> ه وسط
0x00,0x18,0x14,0x14,0x18,0x20,0x20,0x20, //186/ --> ه اخر
0x00,0x21,0x22,0x24,0x28,0x10,0x0F,0x00, //187/ --> لا
0x00,0xB0,0xA8,0x78,0x20,0x20,0x20,0x20, //188/ --> و چسبان
0x20,0x20,0x20,0xA0,0x20,0xA0,0x28,0x30, //189/ --> ی چسبان
0x20,0x20,0x20,0xA0,0x30,0xA0,0x20,0x20, //190/ --> و
0x00,0x60,0x80,0x80,0xA0,0x50,0x10,0x20, //191/ --> ی اخر
0x00,0x1E,0x20,0x20,0x20,0x20,0x20,0x20, //192/ --> ا چسبان
0x00,0x20,0x30,0x28,0x28,0x20,0x00,0x00, //193/ --> ء
0x00,0x04,0x02,0x02,0x3A,0x02,0x02,0x01, //194/ --> آ
0x00,0x00,0x04,0x06,0x3D,0x05,0x04,0x00, //195/ --> أ
0x00,0x00,0x04,0xB6,0xAD,0x7D,0x04,0x00, //196/ --> ؤ
0x00,0x00,0x80,0xC0,0xBF,0xA0,0x80,0x00, //197/ --> إ
0x04,0x66,0x85,0x95,0xA8,0xA8,0x48,0x00, //198/ --> ی همزه دار
0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00, //199/ --> ا
0x00,0x30,0x28,0x20,0xA0,0x20,0x28,0x30, //200/ --> ب
0x00,0x00,0x30,0x2A,0x28,0x32,0x00,0x00, //201/ --> ة
0x00,0x30,0x28,0x22,0x20,0x22,0x28,0x30, //202/ --> ت
0x00,0x30,0x28,0x22,0x21,0x22,0x28,0x30, //203/ --> ث
0x00,0xC0,0xA8,0xA8,0x28,0xB0,0x20,0x20, //204/ --> ج چسبان اخر
0x00,0xC0,0xA8,0xA8,0xA8,0x30,0x20,0x20, //205/ --> ح چسبان اخر
0x00,0xC0,0xA8,0xAA,0x28,0x30,0x20,0x20, //206/ --> خ چسبان اخر
0x00,0x00,0x24,0x24,0x24,0x38,0x00,0x00, //207/ --> د
0x00,0x00,0x24,0x25,0x24,0x38,0x00,0x00, //208/ --> ذ
0x00,0x80,0x80,0x40,0x30,0x00,0x00,0x00, //209/ --> ر
0x00,0x00,0x80,0x80,0x40,0x34,0x00,0x00, //210/ --> ز
0x60,0x80,0x80,0x78,0x20,0x38,0x20,0x18, //211/ --> س
0x60,0x80,0x80,0x78,0x22,0x39,0x22,0x18, //212/ --> ش
0x60,0x80,0x80,0x60,0x30,0x28,0x28,0x18, //213/ --> ص
0x60,0x80,0x80,0x60,0x30,0x28,0x2A,0x18, //214/ --> ض
0x00,0x22,0x14,0x08,0x14,0x22,0x00,0x00, //215/ --> ضربدر
0x20,0x20,0x3E,0x30,0x28,0x28,0x18,0x00, //216/ --> ط
0x20,0x20,0x3E,0x30,0x28,0x2A,0x18,0x00, //217/ --> ظ
0x00,0x00,0x40,0xA0,0xB0,0x28,0x28,0x00, //218/ --> ع
0x00,0x00,0x40,0xA0,0xB0,0x2A,0x28,0x00, //219/ --> غ اخر
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20, //220/ --> خط تیره
0x00,0x18,0x20,0x20,0x30,0x28,0x2A,0x30, //221/ --> ف
0x00,0x60,0x80,0x80,0xB2,0xA8,0x7A,0x00, //222/ --> ق
0x00,0x30,0x28,0x2C,0x2A,0x20,0x3F,0x00, //223/ --> ک
0x00,0x40,0xA9,0xAA,0xA8,0xF0,0x00,0x00, //224/ --> *
0x00,0x00,0x60,0x80,0x80,0x7E,0x00,0x00, //225/ --> ل
0x00,0x40,0xAA,0xA9,0xAA,0xF0,0x00,0x00, //226/ --> *
0x00,0x00,0xC0,0x20,0x30,0x28,0x28,0x30, //227/ --> م
0x00,0x00,0x60,0x80,0x88,0x80,0x60,0x00, //228/ --> ن
0x00,0x00,0x30,0x28,0x28,0x30,0x00,0x00, //229/ --> ه
0x00,0x00,0x00,0xB0,0xA8,0x78,0x00,0x00, //230/ --> و
0x04,0x26,0x25,0x25,0x28,0x10,0x0F,0x00, //231/ --> لک
0x04,0x22,0x22,0x26,0x29,0x10,0x0F,0x00, //232/ --> لخ
0x00,0x21,0x22,0x24,0xA8,0xD0,0xAF,0xA0, //233/ --> لا اخر
0x00,0x70,0xAA,0xA9,0xAA,0x30,0x00,0x00, //234/ --> *
0x00,0x70,0xAA,0xA8,0xAA,0x30,0x00,0x00, //235/ --> *
0x00,0x30,0x40,0x40,0x50,0x28,0x08,0x00, //236/ --> ی
0x00,0x30,0xC0,0x40,0xD0,0x28,0x08,0x00, //237/ --> ی
0x00,0x00,0x02,0x79,0x02,0x00,0x00,0x00, //238/ --> *
0x00,0x00,0x02,0x78,0x02,0x00,0x00,0x00, //239/ --> *
0x00,0x00,0x00,0x00,0x00,0x05,0x05,0x05, //240/ -->ً ً
0x00,0x00,0x00,0x04,0x03,0x0B,0x06,0x06, //241/ --> ً
0xA0,0xA0,0xA0,0x00,0x00,0x00,0x00,0x00, //242/ --> ٍ
0x00,0x00,0x01,0x01,0x01,0x01,0x00,0x00, //243/ --> َ
0x00,0x21,0x22,0x24,0x28,0x10,0x2F,0x20, //244/ --> لا
0x00,0x00,0x00,0x00,0x00,0x04,0x03,0x03, //245/ --> *
0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00, //246/ --> *
0x00,0x00,0x10,0x10,0x54,0x10,0x10,0x00, //247/ --> تفسیم
0x00,0x00,0x02,0x04,0x02,0x04,0x02,0x00, //248/ -->ً تشدید
0x20,0x24,0x26,0x25,0x25,0x20,0x28,0x30, //249/ --> همزه
0x20,0x24,0x26,0x25,0x35,0x20,0x20,0x20, //250/ --> همزه
0x08,0x6C,0x8A,0x8A,0xA0,0x50,0x10,0x20, //251/ --> همزه
0x04,0xB6,0xAD,0x7D,0x24,0x20,0x20,0x20, //252/ --> ؤ
0x00,0x19,0x14,0x15,0x18,0x20,0x20,0x20, //253/ --> ة چسبان
0x04,0x02,0x02,0x1A,0x22,0x22,0x21,0x20, //254/ --> *
0x00,0x40,0x60,0x50,0x48,0x50,0x40,0x40 //255/ --> *
};


#endif /*GLCD_FONT_H_*/