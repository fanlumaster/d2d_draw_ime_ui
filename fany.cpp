﻿#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#include "./fany.h"
#include <comdef.h>
#include <ctime>
#include <d2d1.h>
#include <dwmapi.h>
#include <dwrite.h>
#include <fstream>
#include <iostream>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "dwrite.lib")

ID2D1Factory *factory;
ID2D1HwndRenderTarget *target;
ID2D1SolidColorBrush *solid_brush;
IDWriteFactory *w_factory;
IDWriteTextFormat *w_format;
IDWriteTextLayout *w_layout;
HWND overlayWindow;
HINSTANCE appInstance;
HWND targetWindow;
HWND enumWindow = NULL;
time_t preTime = clock();
time_t showTime = clock();
int fps = 0;

ID2D1Factory *factory2;
ID2D1HwndRenderTarget *target2;
ID2D1SolidColorBrush *solid_brush2;
IDWriteFactory *w_factory2;
IDWriteTextFormat *w_format2;
IDWriteTextLayout *w_layout2;
HWND overlayWindow2;
HINSTANCE appInstance2;
HWND targetWindow2;
HWND enumWindow2 = NULL;
time_t preTime2 = clock();
time_t showTime2 = clock();
int fps2 = 0;

bool o_Foreground = false;
bool o_DrawFPS = false;
bool o_VSync = false;
// std::wstring fontname = L"Courier";
std::wstring fontname = L"微软雅黑";

DirectOverlayCallback drawLoopCallback = NULL;
DirectOverlayCallback drawLoopCallback2 = NULL;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowProc2(HWND hwnd, UINT uMsg, WPARAM wParam,
                             LPARAM lParam);

void DrawString(std::string str, float fontSize, float x, float y, float r,
                float g, float b, float a) {
  RECT re;
  GetClientRect(overlayWindow, &re);
  FLOAT dpix, dpiy;
  dpix = static_cast<float>(re.right - re.left);
  dpiy = static_cast<float>(re.bottom - re.top);
  HRESULT res = w_factory->CreateTextLayout(
      std::wstring(str.begin(), str.end()).c_str(), str.length() + 1, w_format,
      dpix, dpiy, &w_layout);
  if (SUCCEEDED(res)) {
    DWRITE_TEXT_RANGE range;
    range.startPosition = 0;
    range.length = str.length();
    w_layout->SetFontSize(fontSize, range);
    solid_brush->SetColor(D2D1::ColorF(r, g, b, a));
    target->DrawTextLayout(D2D1::Point2F(x, y), w_layout, solid_brush);
    w_layout->Release();
    w_layout = NULL;
  }
}

void DrawString2(std::string str, float fontSize, float x, float y, float r,
                 float g, float b, float a) {
  RECT re;
  GetClientRect(overlayWindow2, &re);
  FLOAT dpix, dpiy;
  dpix = static_cast<float>(re.right - re.left);
  dpiy = static_cast<float>(re.bottom - re.top);
  HRESULT res = w_factory2->CreateTextLayout(
      std::wstring(str.begin(), str.end()).c_str(), str.length() + 1, w_format2,
      dpix, dpiy, &w_layout2);
  if (SUCCEEDED(res)) {
    DWRITE_TEXT_RANGE range;
    range.startPosition = 0;
    range.length = str.length();
    w_layout2->SetFontSize(fontSize, range);
    solid_brush2->SetColor(D2D1::ColorF(r, g, b, a));
    target2->DrawTextLayout(D2D1::Point2F(x, y), w_layout2, solid_brush2);
    w_layout2->Release();
    w_layout2 = NULL;
  }
}

void DrawString3(std::wstring str, float fontSize, float x, float y, float r,
                 float g, float b, float a) {
  RECT re;
  GetClientRect(overlayWindow2, &re);
  FLOAT dpix, dpiy;
  dpix = static_cast<float>(re.right - re.left);
  dpiy = static_cast<float>(re.bottom - re.top);
  HRESULT res = w_factory2->CreateTextLayout(
      std::wstring(str.begin(), str.end()).c_str(), str.length() + 1, w_format2,
      dpix, dpiy, &w_layout2);
  if (SUCCEEDED(res)) {
    DWRITE_TEXT_RANGE range;
    range.startPosition = 0;
    range.length = str.length();
    w_layout2->SetFontSize(fontSize, range);

    // solid_brush2->SetColor(D2D1::ColorF(255, 255, 255, 1));
    solid_brush2->SetColor(D2D1::ColorF(68.0f / 255.0f, 68.0f / 255.0f, 68.0f / 255.0f, 1.0f));
    D2D1_RECT_F rect = D2D1::RectF(10.0f, 116.0f, 128.0f, 338.0f);
    D2D1_ROUNDED_RECT rounded_rect = D2D1::RoundedRect(rect, 8, 8);
    // target2->DrawRectangle(rect, solid_brush2, 2.0f);
    // target2->FillRectangle(rect, solid_brush2);
    target2->FillRoundedRectangle(rounded_rect, solid_brush2);

    // solid_brush2->SetColor(D2D1::ColorF(r, g, b, a));
    solid_brush2->SetColor(D2D1::ColorF(238.0f / 255.0f, 236.0f / 255.0f, 226.0f / 255.0f, 1.0f));
    target2->DrawTextLayout(D2D1::Point2F(x, y), w_layout2, solid_brush2);
    w_layout2->Release();
    w_layout2 = NULL;
  }
}

void DrawBox(float x, float y, float width, float height, float thickness,
             float r, float g, float b, float a, bool filled) {
  solid_brush->SetColor(D2D1::ColorF(r, g, b, a));
  if (filled)
    target->FillRectangle(D2D1::RectF(x, y, x + width, y + height),
                          solid_brush);
  else
    target->DrawRectangle(D2D1::RectF(x, y, x + width, y + height), solid_brush,
                          thickness);
}

void DrawLine(float x1, float y1, float x2, float y2, float thickness, float r,
              float g, float b, float a) {
  solid_brush->SetColor(D2D1::ColorF(r, g, b, a));
  target->DrawLine(D2D1::Point2F(x1, y1), D2D1::Point2F(x2, y2), solid_brush,
                   thickness);
}

void DrawCircle(float x, float y, float radius, float thickness, float r,
                float g, float b, float a, bool filled) {
  solid_brush->SetColor(D2D1::ColorF(r, g, b, a));
  if (filled)
    target->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius),
                        solid_brush);
  else
    target->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius),
                        solid_brush, thickness);
}

void DrawEllipse(float x, float y, float width, float height, float thickness,
                 float r, float g, float b, float a, bool filled) {
  solid_brush->SetColor(D2D1::ColorF(r, g, b, a));
  if (filled)
    target->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), width, height),
                        solid_brush);
  else
    target->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), width, height),
                        solid_brush, thickness);
}

void d2oSetup(HWND tWindow) {
  targetWindow = tWindow;
  WNDCLASS wc = {};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = GetModuleHandle(0);
  wc.lpszClassName = L"d2do";
  RegisterClass(&wc);
  overlayWindow = CreateWindowEx(
      WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
      wc.lpszClassName, L"D2D Overlay", WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, wc.hInstance, NULL);

  MARGINS mar = {-1};
  DwmExtendFrameIntoClientArea(overlayWindow, &mar);
  D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory);
  factory->CreateHwndRenderTarget(
      D2D1::RenderTargetProperties(
          D2D1_RENDER_TARGET_TYPE_DEFAULT,
          D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN,
                            D2D1_ALPHA_MODE_PREMULTIPLIED)),
      D2D1::HwndRenderTargetProperties(overlayWindow, D2D1::SizeU(200, 200),
                                       D2D1_PRESENT_OPTIONS_IMMEDIATELY),
      &target);
  target->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f), &solid_brush);
  target->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
  DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
                      reinterpret_cast<IUnknown **>(&w_factory));
  w_factory->CreateTextFormat(fontname.c_str(), NULL, DWRITE_FONT_WEIGHT_NORMAL,
                              DWRITE_FONT_STYLE_NORMAL,
                              DWRITE_FONT_STRETCH_NORMAL, 10.0f, L"en-us",
                              &w_format);
}

void d2oSetup2(HWND tWindow) {
  targetWindow2 = tWindow;
  WNDCLASS wc = {};
  wc.lpfnWndProc = WindowProc2;
  wc.hInstance = GetModuleHandle(0);
  wc.lpszClassName = L"d2do2";
  RegisterClass(&wc);
  overlayWindow2 = CreateWindowEx(
      WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
      wc.lpszClassName, L"D2D Overlay2", WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, wc.hInstance, NULL);

  MARGINS mar = {-1};
  DwmExtendFrameIntoClientArea(overlayWindow2, &mar);
  D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory2);
  factory2->CreateHwndRenderTarget(
      D2D1::RenderTargetProperties(
          D2D1_RENDER_TARGET_TYPE_DEFAULT,
          D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN,
                            D2D1_ALPHA_MODE_PREMULTIPLIED)),
      D2D1::HwndRenderTargetProperties(overlayWindow2, D2D1::SizeU(200, 200),
                                       D2D1_PRESENT_OPTIONS_IMMEDIATELY),
      &target2);
  target2->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f), &solid_brush2);
  target2->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
  DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
                      reinterpret_cast<IUnknown **>(&w_factory2));
  w_factory2->CreateTextFormat(
      fontname.c_str(), NULL, DWRITE_FONT_WEIGHT_NORMAL,
      DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 10.0f, L"en-us",
      &w_format2);
}

void mainLoop() {
  MSG message;
  message.message = WM_NULL;
  ShowWindow(overlayWindow, 1);
  UpdateWindow(overlayWindow);
  SetLayeredWindowAttributes(overlayWindow, RGB(0, 0, 0), 255, LWA_ALPHA);
  if (message.message != WM_QUIT) {
    if (PeekMessage(&message, overlayWindow, NULL, NULL, PM_REMOVE)) {
      TranslateMessage(&message);
      DispatchMessage(&message);
    }

    UpdateWindow(overlayWindow);
    WINDOWINFO info;
    ZeroMemory(&info, sizeof(info));
    info.cbSize = sizeof(info);
    GetWindowInfo(targetWindow, &info);
    D2D1_SIZE_U siz;
    siz.height = ((info.rcClient.bottom) - (info.rcClient.top));
    siz.width = ((info.rcClient.right) - (info.rcClient.left));
    if (!IsIconic(overlayWindow)) {
      SetWindowPos(overlayWindow, NULL, info.rcClient.left, info.rcClient.top,
                   siz.width, siz.height, SWP_SHOWWINDOW);
      target->Resize(&siz);
    }
    target->BeginDraw();
    target->Clear(D2D1::ColorF(0, 0, 0, 0));
    if (drawLoopCallback != NULL) {
      if (o_Foreground) {
        if (GetForegroundWindow() == targetWindow)
          goto toDraw;
        else
          goto noDraw;
      }

    toDraw:
      time_t postTime = clock();
      time_t frameTime = postTime - preTime;
      preTime = postTime;

      if (o_DrawFPS) {
        if (postTime - showTime > 100) {
          fps = 1000 / (float)frameTime;
          showTime = postTime;
        }
        DrawString(std::to_string(fps), 20, 30, 50, 0, 1, 0, 1);
      }

      if (o_VSync) {
        int pausetime = 17 - frameTime;
        if (pausetime > 0 && pausetime < 30) {
          Sleep(pausetime);
        }
      }

      drawLoopCallback(siz.width, siz.height);
    }
  noDraw:
    target->EndDraw();
    Sleep(1);
  }
}

void mainLoop2() {
  MSG message;
  message.message = WM_NULL;
  ShowWindow(overlayWindow2, 1);
  UpdateWindow(overlayWindow2);
  SetLayeredWindowAttributes(overlayWindow2, RGB(0, 0, 0), 255, LWA_ALPHA);
  if (message.message != WM_QUIT) {
    if (PeekMessage(&message, overlayWindow2, NULL, NULL, PM_REMOVE)) {
      TranslateMessage(&message);
      DispatchMessage(&message);
    }

    UpdateWindow(overlayWindow2);
    WINDOWINFO info;
    ZeroMemory(&info, sizeof(info));
    info.cbSize = sizeof(info);
    GetWindowInfo(targetWindow2, &info);
    D2D1_SIZE_U siz;
    siz.height = ((info.rcClient.bottom) - (info.rcClient.top));
    siz.width = ((info.rcClient.right) - (info.rcClient.left));
    if (!IsIconic(overlayWindow2)) {
      SetWindowPos(overlayWindow2, NULL, info.rcClient.left, info.rcClient.top,
                   siz.width, siz.height, SWP_SHOWWINDOW);
      target2->Resize(&siz);
    }
    target2->BeginDraw();
    target2->Clear(D2D1::ColorF(0, 0, 0, 0));
    if (drawLoopCallback2 != NULL) {
      if (o_Foreground) {
        if (GetForegroundWindow() == targetWindow2)
          goto toDraw;
        else
          goto noDraw;
      }

    toDraw:
      time_t postTime = clock();
      time_t frameTime = postTime - preTime;
      preTime = postTime;

      if (o_DrawFPS) {
        if (postTime - showTime > 100) {
          fps2 = 1000 / (float)frameTime;
          showTime = postTime;
        }
        DrawString2(std::to_string(fps2), 20, siz.width - 50, 0, 0, 1, 0, 1);
      }

      if (o_VSync) {
        int pausetime = 17 - frameTime;
        if (pausetime > 0 && pausetime < 30) {
          Sleep(pausetime);
        }
      }

      drawLoopCallback2(siz.width, siz.height);
    }
  noDraw:
    target2->EndDraw();
    Sleep(1);
  }
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uiMessage, WPARAM wParam,
                            LPARAM lParam) {
  switch (uiMessage) {
  case WM_CLOSE:
    DestroyWindow(hWnd);
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, uiMessage, wParam, lParam);
  }
  return 0;
}

LRESULT CALLBACK WindowProc2(HWND hWnd, UINT uiMessage, WPARAM wParam,
                             LPARAM lParam) {
  switch (uiMessage) {
  case WM_CLOSE:
    DestroyWindow(hWnd);
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, uiMessage, wParam, lParam);
  }
  return 0;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
  DWORD lpdwProcessId;
  GetWindowThreadProcessId(hwnd, &lpdwProcessId);
  if (lpdwProcessId == GetCurrentProcessId()) {
    enumWindow = hwnd;
    return FALSE;
  }
  return TRUE;
}

DWORD WINAPI OverlayThread(LPVOID lpParam) {
  enumWindow = (HWND)lpParam;
  d2oSetup(enumWindow);
  for (;;) {
    mainLoop();
  }
}

DWORD WINAPI OverlayThread2(LPVOID lpParam) {
  enumWindow2 = (HWND)lpParam;
  d2oSetup2(enumWindow2);
  for (;;) {
    mainLoop2();
  }
}

void DirectOverlaySetup(DirectOverlayCallback callback) {
  drawLoopCallback = callback;
  CreateThread(0, 0, OverlayThread, NULL, 0, NULL);
}

void DirectOverlaySetup(DirectOverlayCallback callback, HWND _targetWindow) {
  drawLoopCallback = callback;
  CreateThread(0, 0, OverlayThread, _targetWindow, 0, NULL);
}

void DirectOverlaySetup2(DirectOverlayCallback callback, HWND _targetWindow) {
  drawLoopCallback2 = callback;
  CreateThread(0, 0, OverlayThread2, _targetWindow, 0, NULL);
}

void DirectOverlaySetOption(DWORD option) {
  if (option & D2DOV_REQUIRE_FOREGROUND)
    o_Foreground = true;
  if (option & D2DOV_DRAW_FPS)
    o_DrawFPS = true;
  if (option & D2DOV_VSYNC)
    o_VSync = true;
  if (option & D2DOV_FONT_ARIAL)
    fontname = L"arial";
  if (option & D2DOV_FONT_COURIER)
    fontname = L"Courier";
  if (option & D2DOV_FONT_CALIBRI)
    fontname = L"Calibri";
  if (option & D2DOV_FONT_GABRIOLA)
    fontname = L"Gabriola";
  if (option & D2DOV_FONT_IMPACT)
    fontname = L"Impact";
}

void drawLoop(int width, int height) {
  // DrawLine(0, 0, 100, 100, 5, 1, 1, 0, .8);
  DrawString("The quick brown fox jumped over the lazy dog.", 36, 10, 10, 0, 1,
             1, 1);
  // DrawBox(100, 100, 100, 100, 5, 0, 1, 0, 1, 0);
  // DrawCircle(50, 50, 20, 1, 1, 0, 0, .25, 1);
  // DrawEllipse(500, 100, 50, 20, 5, 1, 0, 0, 1, 0);
}

void drawLoop02(int width, int height) {
  // DrawString2("Quick fox? Yeah, this is the second window.", 36, 10, 80, 0,
  // 1,
  //             1, 1);
  // DrawString2("1. hello\n2. what\n3. fany\n4. full\n5. world", 36, 10, 120,
  // 0,
  //             1, 1, 1);

  // DrawString3(L"1. hello\n2. what\n3. fany\n4. full\n5. world\n6. window\n7. time\n8. hey", 18, 15, 120, 0,
  //             1, 1, 1);
  DrawString3(L"ll'zi\n1. 量子 ov\n2. 笔画\n3. 毛笔\n4. 测试\n5. 什么\n6. 微软\n7. 竟然\n8. 可是", 18, 15, 120, 0,
              1, 1, 1);
}

void drawLoop03(int width, int height) {
  // DrawString2("Quick fox? Yeah, this is the second window.", 36, 10, 80, 0,
  // 1,
  //             1, 1);
  // DrawString2("1. hello\n2. what\n3. fany\n4. full\n5. world", 36, 10, 120,
  // 0,
  //             1, 1, 1);

  // DrawString3(L"1. hello\n2. what\n3. fany\n4. full\n5. world\n6. window\n7. time\n8. hey", 18, 15, 120, 0,
  //             1, 1, 1);
  DrawString3(L"ll'zi\n1. 量子 ov\n2. 两字 ab\n3. 梁子 mv\n4. 良子 dv\n5. 凉子 dv\n6. 亮子 wv\n7. 梁紫 ms\n8. 两 ad", 18, 15, 120, 0,
              1, 1, 1);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {

  // DirectOverlaySetOption(D2DOV_FONT_IMPACT | D2DOV_DRAW_FPS);
  HWND desktopHwnd = GetDesktopWindow();
  // 这是另一个线程
  // DirectOverlaySetup(drawLoop, FindWindowW(NULL, L"Fany"));
  DirectOverlaySetup(drawLoop, desktopHwnd);
  // DirectOverlaySetup2(drawLoop02, desktopHwnd);
  DirectOverlaySetup2(drawLoop03, desktopHwnd);

  MSG msg;
  ZeroMemory(&msg, sizeof(msg));

  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return msg.wParam;
}
