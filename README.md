# 📁 基于多态架构的坦克对战系统 (Tank Battle C++ Core)

[![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.7-white?logo=unrealengine&logoColor=white&color=0E1128)](https://www.unrealengine.com/)
[![Language](https://img.shields.io/badge/Language-C++-blue.svg)](https://isocpp.org/)

## 📝 项目简介
本项目是一个侧重于 **C++ 类层级设计** 与 **物理手感调优** 的模拟战斗项目。通过深度应用 C++ 的继承与多态特性，构建了一套高复用性的载具战斗框架。项目核心展示了如何通过纯代码实现丝滑的炮塔转向、物理弹道计算及高性能的 AI 调度逻辑。

> [!IMPORTANT]
> **注意：** 本仓库为 **Code-Only** 模式，仅包含 `Source` 目录下的 C++ 核心源码。美术资产（模型、特效）未上传，核心逻辑实现请参考源码及注释。

---

## 🛠 技术栈 (Tech Stack)

| 分类 | 工具/技术 |
| :--- | :--- |
| **引擎版本** | **Unreal Engine 5.7** |
| **核心语言** | **C++** (底层逻辑), **Blueprints** (UI 与数据配置) |
| **版本控制** | **Git** |
| **开发环境** | **Visual Studio**, **GitHub Copilot** (AI 辅助逻辑优化) |

---

## 🧠 核心模块深度解析

### 1. 类继承架构 (Class Inheritance)
* **核心类：** `BasePawn.cpp`
* **设计模式：** 抽象出 `BasePawn` 作为所有战斗单位的基类，封装了基础机构创建（方便蓝图制作）、炮塔旋转逻辑、开火以及销毁（包含摄像机抖动与死亡音效）逻辑。
* **逻辑扩展：** * **Tank.cpp (玩家类)：** 独立实现增强输入绑定与底盘移动，重写玩家控制的炮塔旋转，增添摄像机弹簧臂组件，并丰富了死亡逻辑。
    * **Tower.cpp (AI类)：** 独立实现基于距离检测的自动追踪与攻击决策。
* **价值：** 该设计实现了 **80% 的代码复用**，显著降低了逻辑维护成本。

### 2. 物理手感的优化 (Physics Smoothing)
* **技术实现：** 弃用瞬时转向，采用 `FMath::RInterpTo` 算法。
* **细节优化：** 结合 `GetWorldDeltaSeconds` 确保了炮塔转向在不同帧率下均能保持相同的动态阻尼感。通过 C++ 底层参数微调，还原了重型载具的物理质量感。

### 3. 采用定时器优化 AI 开火节奏 (Timer Optimization)
* **优化策略：** 针对 AI 开火频率与玩家探测逻辑，**完全弃用 `Tick` 每帧轮询**。
* **技术实现：** 采用 `FTimerHandle` 驱动 AI 决策循环。这种基于事件/时间的调度方式极大地降低了场景中多单位存在时的 CPU 计算负载。

### 4. 物理弹道与生命组件 (Projectile & Health)
* **弹道模拟：** 自定义 `Projectile` 类，利用 `ProjectileMovementComponent` 模拟真实初速与重力感应。
* **组件化生命值：** 开发独立的 `HealthComponent`，通过 **委托 (Delegates)** 与 `Projectile` 通信，使拥有该组件的 Actor 可以正常实现受击和死亡逻辑。

---

## 📂 如何阅读本项目 (How to Navigate)

由于缺少资产，源码主要集中在 `Source/` 目录下。建议重点审阅以下核心路径：

* **底层基类：** `Source/.../BasePawn.cpp` 
    * *关键点：函数的定义以及各子类共用接口的抽象。*
* **玩家控制器：** `Source/.../Tank.cpp` 
    * *关键点：如何将输入映射转化为复杂的物理位移。*
* **AI 决策逻辑：** `Source/.../Tower.cpp` 
    * *关键点：`FTimerHandle` 的应用以及目标检测逻辑。*
* **物理碰撞处理：** `Source/.../Projectile.cpp`
    * *关键点：命中判定与径向伤害 (`ApplyRadialDamage`) 的触发。*

> **提示：** 源码中关键逻辑均附带详细的中文注释及目录说明。

---

## 📜 许可声明 (License)
本项目仅用于个人学习交流与作品集展示。素材引用自公开资源（如虚幻商城等）。
