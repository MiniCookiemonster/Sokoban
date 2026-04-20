# Sokoban Win32 Game

这是一个使用 Win32 API 和 GDI 绘制的推箱子小游戏示例，适合作为课程设计或大学 C++/Windows 程序设计项目继续扩展。

## 已实现功能

- Win32 窗口程序入口 `WinMain`
- 使用方向键或 `W/A/S/D` 控制玩家移动
- 墙体碰撞检测，玩家不能穿墙
- 箱子推动检测，箱子前方有墙或其他箱子时不能推动
- 简单卡箱/死角提示：箱子被推到非目标点墙角时会提示
- 步数统计
- 移动历史记录，右侧面板显示最近 12 步
- 胜利判断：所有箱子都在目标点上
- `R` 键重置当前关卡
- 支持从 `levels/level1.txt` 读取关卡，读取失败时自动使用内置默认关卡

## 地图符号

```text
# 墙
. 目标点
$ 箱子
@ 玩家
* 已在目标点上的箱子
+ 站在目标点上的玩家
  空地
```

## 构建方式

需要安装 Visual Studio C++ 工具链和 CMake。

```powershell
cmake -S . -B build
cmake --build build
```

构建完成后运行生成的 `Sokoban.exe`。

## 项目结构

```text
sokoban-win32/
  CMakeLists.txt
  README.md
  levels/
    level1.txt
  src/
    main.cpp      Win32 窗口、消息循环、键盘消息
    game.h/.cpp   游戏规则、移动、步数、胜利判断
    level.h/.cpp  关卡读取、地图访问、重置
    history.h/.cpp 历史记录
    input.h/.cpp  键盘到方向的转换
    renderer.h/.cpp Win32/GDI 绘制
```

## 可继续扩展的方向

- 增加多关卡和下一关按钮
- 增加撤销功能，把每一步的完整地图快照保存到历史记录
- 使用位图资源替换当前的色块绘制
- 增加菜单栏、计时器和最佳成绩保存
