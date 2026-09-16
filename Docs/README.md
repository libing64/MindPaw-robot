# ubuntu24.04 创建编译环境并烧录 

本机 ESP8266 开发环境已经打通：编译、烧录、启动都已验证。

**工具链**
- 已安装 PlatformIO Core **6.1.18**（`~/.local/bin/pio`）
- 板子：CH340 → `/dev/ttyUSB0`，芯片 `ESP8266EX`，MAC `98:f4:ab:d8:db:69`

**工程**
- [`MindPaw_main/platformio.ini`](MindPaw_main/platformio.ini) 增加了 `monitor_speed = 115200`、`upload_speed = 115200`
- 首次从 GitHub 拉 ArduCAM 失败（TLS 中断），已用镜像装进本地依赖，后续 `pio run` 可直接编

**编译修复**（否则固件编不过）
- `streaming_recon.cpp`：Bearer 头改为 `addHeader`，不能把运行时字符串和字面量拼在一起
- `streaming_recon.h`：`_buildMultipartBody` 改为非 static，才能用 `_fps`

**烧录结果**
- 固件 + SPIFFS（12 个网页）均已写入
- 串口确认：`热点已启动` / `访问地址: 192.168.4.1`，语音、摄像头、情感引擎也初始化成功

**以后常用命令**

```bash
pio run --project-dir MindPaw_main
pio run --project-dir MindPaw_main -t upload --upload-port /dev/ttyUSB0
pio run --project-dir MindPaw_main -t uploadfs --upload-port /dev/ttyUSB0
pio device monitor --project-dir MindPaw_main --port /dev/ttyUSB0 --baud 115200
```

手机连 WiFi **MindPaw**（密码 `mindpaw1234`），浏览器打开 `http://192.168.4.1` 即可控制。


# 接入OLED

MindPaw 用的是 **SSD1306 128×64 I2C OLED**。固件里时钟是 GPIO5、数据是 GPIO4：

```53:53:MindPaw_main/src/main.cpp
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE, /* clock=*/5, /* data=*/4);
```

**接线（4 根线）：**

| OLED 引脚 | ESP8266 / NodeMCU | 说明 |
|-----------|-------------------|------|
| VCC | **3.3V** | 不要接 5V |
| GND | **GND** | 与开发板共地 |
| SDA | **GPIO4（D2）** | I2C 数据 |
| SCL | **GPIO5（D1）** | I2C 时钟 |

SDA、SCL 各用 **4.7kΩ 上拉到 3.3V**。很多成品 OLED 模块板上已经有上拉，杜邦线直连即可；裸屏或没有上拉的模块必须外加上拉。

```
ESP8266 / NodeMCU          SSD1306 OLED
┌─────────────┐            ┌──────────┐
│ 3.3V        ├────────────┤ VCC      │
│ GND         ├────────────┤ GND      │
│ D2 / GPIO4  ├──── SDA ───┤ SDA      │
│ D1 / GPIO5  ├──── SCL ───┤ SCL      │
└─────────────┘            └──────────┘
```

**注意：**
- 模块如果有 `RES/RST`，可以悬空（固件设了 `U8X8_PIN_NONE`）。
- I2C 地址一般是 **0x3C**。
- 舵机用 5V，OLED 只用 3.3V。

上电后屏幕应先出 Logo，再显示 WiFi 信息。不亮时优先查：VCC 是否 3.3V、SDA/SCL 是否接反、上拉是否到位。完整引脚表见 [`MindPaw_main/PIN_WIRING.md`](MindPaw_main/PIN_WIRING.md)。

# WIFI连接 & 网页访问 

原来的首页是登录页，姓名必须是 **庹忠曜** 或 **王家丽** 才能进控制台，看起来就像“没内容”。

**已经改好并重新烧录：**
- 打开 `http://192.168.4.1` 直接进控制菜单（`home.html`）
- 登录页不再校验姓名
- 网页文件缺失时会提示去执行 `uploadfs`，不再给空白 404

**请用手机再试一次：**
1. 连 WiFi **MindPaw**，密码 `mindpaw1234`
2. 若提示“已连接，但无法访问互联网”，选 **仍要使用 / 保持连接**
3. 浏览器打开 **`http://192.168.4.1`**（必须是 http，不要 https）
4. 应看到运动、表情等入口

不要用这台已连公司/家庭网的电脑去访问 `192.168.4.1`。要用电脑打开网页，先把电脑也连上 MindPaw 热点。