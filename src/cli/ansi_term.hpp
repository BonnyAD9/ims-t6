#pragma once

#define CSI "\x1b["

#define CSI_FORMAT(v) CSI #v "m"

#define RESET CSI_FORMAT(0)

#define BOLD CSI_FORMAT(1)
#define ITALIC CSI_FORMAT(3)

#define DYELLOW CSI_FORMAT(33)

#define DGRAY CSI_FORMAT(90)
#define RED CSI_FORMAT(91)
#define GREEN CSI_FORMAT(92)
#define YELLOW CSI_FORMAT(93)
#define BLUE CSI_FORMAT(94)
#define MAGENTA CSI_FORMAT(95)
#define CYAN CSI_FORMAT(96)
#define WHITE CSI_FORMAT(97)

#define RGB(r, g, b) CSI "38;2;" #r ";" #g ";" #b "m"
