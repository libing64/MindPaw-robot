//----------------------------------------------
// OV2640 摄像头模块 (ArduCAM Mini SPI)
// 简化版 — 负责原始帧捕获和灰度缓冲提取
// 手势分类委托给 GestureNN 模块
//----------------------------------------------
#ifndef OV2640_H
#define OV2640_H

#include <Arduino.h>
#include <ArduCAM.h>
#include <SPI.h>

//============================================================
// 引脚配置 — 根据实际接线修改
//============================================================
#define OV2640_CS   D8       // 片选 (GPIO15)
// OV2640 使用硬件 SPI，与 SD 卡等共享 SPI 总线
//============================================================

// 灰度图目标尺寸 (用于 GestureNN 推理)
#define CAM_GRAY_W  40
#define CAM_GRAY_H  30

class OV2640_Camera {
public:
    OV2640_Camera(uint8_t csPin = OV2640_CS);

    // 初始化摄像头，返回是否成功
    bool begin();

    // 捕获一帧并下采样到 40×30 灰度缓冲
    // buffer: 必须至少 1200 字节 (40×30)
    // 返回: true=成功, false=失败
    bool captureGrayscale(uint8_t* buffer);

    // 设置捕获间隔 (ms，默认 500)
    void setInterval(unsigned long ms) { _intervalMs = ms; }

    // 检测是否可用
    bool isAvailable() const { return _available; }

    // 捕获计时 (用于 loop 节流)
    unsigned long getLastCaptureMs() const { return _lastCaptureMs; }
    unsigned long getIntervalMs() const { return _intervalMs; }

    // 设置调试输出
    void setDebug(bool debug) { _debug = debug; }

private:
    ArduCAM* _cam;
    uint8_t _cs;
    bool _available;
    bool _debug;
    unsigned long _lastCaptureMs;
    unsigned long _intervalMs;

    bool initCamera();
    bool captureRawFrame();
    void sampleToGrayscale(uint8_t* buffer, int srcW, int srcH, int dstW, int dstH);
    uint16_t readFifoWord();
};

#endif // OV2640_H
