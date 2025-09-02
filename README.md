# Godot MyPerfBullets-CN
![PerfBulletsLogo - 副本](https://github.com/Moonzel/Godot-PerfBullets/assets/96361809/e3c2392a-09f8-4cf9-b98b-f213b233ae62)

## 来源

[Godot-PerfBullets](https://github.com/Moonzel/Godot-PerfBullets)

感谢[Moonzel](https://github.com/Moonzel)的精彩创作。

部分功能至少在思路上来源[nikoladevelops/godot-blast-bullets-2d](https://github.com/nikoladevelops/godot-blast-bullets-2d)。感谢创作！

## 不同

- 已实现
    - 为子弹资源类和运行时类添加自定义数据字典属性，为子弹运行时类添加对子弹资源的引用
- TODO
    - 中文类文档
    - 模仿[nikoladevelops/godot-blast-bullets-2d](https://github.com/nikoladevelops/godot-blast-bullets-2d)的附加节点及对象池功能
        - 可能会在C++中利用多重继承创建一些直接可用的节点
    - 禁用物理功能
    - 可能会改造插件有关子弹移动部分，将部分职能移交到附加节点，并提供一些静态C++方法优化性能
    - 探索GDS直接覆盖C++方法的可能性

## 以极高的性能在屏幕上生成数千颗子弹或粒子！

<p align="center">
  <img src="https://github.com/Moonzel/Public_Gifs_For_Projects_Moonzel/blob/main/HomingDemo.gif" width="480" />
  <img src="https://github.com/Moonzel/Public_Gifs_For_Projects_Moonzel/blob/main/SpiralDemo.gif" width="480" />
  <img src="https://github.com/Moonzel/Public_Gifs_For_Projects_Moonzel/blob/main/StressDemo.gif" width="480" />
</p>

此插件适用于 **GDExtension**，与 Godot 4.4.1 兼容，应该支持更高版本，但很可能不支持更低版本，且仅支持移动端或 Forward+ 渲染器。<br>

包含的版本已预编译，适用于 Windows。

## 主要特性

- 生成高性能子弹，使用 C++ 编写以实现最大性能
- 使用精灵表动画化子弹，同时保留多网格的优势
- 使用自定义碰撞形状和自定义遮罩
- 选择处理模式或物理处理模式来移动子弹
- 为子弹创建边界，使其在特定距离处消失（使用 BulletBorder 类）
- 设置子弹追踪特定节点
- 使用 PatternManager 类轻松创建多个生成器的模式
- 创建多个子弹数组以设计更复杂的模式

### 基本设置

### 前六个步骤对于生成器正常工作至关重要

1. 确保在项目设置中激活了 `PerfBullets` 插件。
2. 添加一个基础场景节点作为 Node2D（或任何继承自该类的节点）。
3. 添加一个 Spawner 节点作为子节点。
4. 在 `Bullet Type` 属性中创建一个 BulletType 资源。
5. 设置该 BulletType 资源的形状（用于碰撞）。
6. 在节点的 MultiMeshInstance2D 部分设置节点的纹理（如果使用动画，则设置精灵表）。
#### 其余步骤是可选的，但建议充分利用插件功能。
6. 添加一个 BulletBorder 节点作为主节点的子节点。
7. 创建两个 Node2D 作为该节点的子节点。
8. 选择一个节点作为 `TopLeft` 属性，另一个作为 `BottomRight` 属性（这将创建边界）。
9. 添加一个 PatternManager 节点。
10. 为场景中的**每一个** Spawner 节点添加一个 PatternSpawnerData 资源。
11. 设置生成器的 ID、激活前的时间以及计时器的模式。
12. 如果使用 PatternManager，将生成器的模式更改为 `PATTERNMANAGER`。
13. 选择生成器并转到信号选项卡。
14. 将 `bullet_hit` 信号添加到处理子弹行为的节点。
	- 可以选择将多个信号添加到同一个函数。
 	- 当将信号添加到接收信号的节点时，按下标有 `pick` 的按钮。
	- 然后选择要添加到的函数，允许多个生成器使用同一个信号。

### 预期效果如下：
<img src="https://github.com/Moonzel/Public_Gifs_For_Projects_Moonzel/blob/main/BasicDemoUpdated.gif" />

## 示例
在仓库中，有一个名为 `examples` 的文件夹，包含一些示例，您可以基于这些示例开发游戏：

 - `stress_test`：此示例通过生成大量旋转模式的子弹展示插件的性能。
 - `aimed_at_player`：此示例展示生成器如何朝向玩家方向启动，使用偏移量使射击直接指向玩家。
 - `basic_setup`：此示例展示生成器的最基本实现，可作为新模式的起点。
 - `basic_setup_with_PatternManager`：与上一个示例相同，但增加了 PatternManager。
 - `node_hierarchy`：此示例展示生成器无论作为谁的子节点都能正常工作，甚至可以在移动的父节点下保持静止（参见 moveWithParent）。

## 完整文档

见[ClassDocumentation](ClassDocumentation.md)

TODO:未来将会在Godot编辑器中可见

## 编辑插件的说明
### 在项目开发过程中，您可能会需要某个特定功能，而基础插件中并未包含。如果发生这种情况，您可以自行编辑插件。

**如果不熟悉 C++，请使用以下链接入门：**
- https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html (Godot 官方文档)
- https://www.youtube.com/playlist?list=PLhixpuPeRv9aDdsZbhTpsXguYRvMgyVQ- (moshen zare 的 GDExtension 教程)

#### 使用 C++ 编辑插件的步骤
*假设您已在当前项目中安装了插件*

1. 参考[how-to-install-c-and-cpp-compiler-on-windows](https://www.freecodecamp.org/news/how-to-install-c-and-cpp-compiler-on-windows/)下载安装C++
2. 从 https://github.com/godotengine/godot-cpp 下载相应分支（您的版本）的 C++ 代码。
3. 将 `godot-cpp-4.x` 文件夹粘贴到 `addons/PerfBullets` 文件夹中。
4. 下载 SCons：
   - 打开 Windows PowerShell 或终端。
   - 运行 `Set-ExecutionPolicy RemoteSigned -scope CurrentUser`。
   - 如果提示，按 "Y"。
   - 然后运行 `iwr -useb get.scoop.sh | iex`。
   - 最后运行 `scoop install gcc python scons make mingw`。
5. 将 `godot-cpp-4.x` 重命名为 `godot-cpp`。
6. 进入 `godot-cpp` 文件夹，并在该位置打开终端或命令行（使用 cd 命令）。
    - TODO:不清楚直接在`addons/PerfBullets` 文件夹编译会如何。因为后面发现godot-cpp似乎编译了两次。
7. 运行 `scons`，等待绑定安装完成。个人不建议在 vscode 终端中编译，因为速度会很慢很慢！
8. 在代码编辑器（如 Visual Studio）中打开插件。
   - 确保所选代码编辑器中的所有路径都正确，以免出现错误。
9. 对插件进行更改。
10. 进入 `addons/PerfBullets` 文件夹，并在该位置打开终端或命令行（使用 cd 命令）。
11. 最后在 Godot **未打开**的情况下运行 `scons`。
12. 应该已成功更新插件的 C++ 部分。

#### 可能出现的错误

- SCons 可能未选择正确的编译器。请仔细检查是否有其他软件自动将编译器设置为不正确。
- 主文件夹中可能存在 `.gdignore` 文件，导致 Godot 无法访问类。在 `/src` 文件夹中**应该**有一个这样的文件。
- 检查文件放置位置以及 SConstruct 文件中的路径。
- 如果以上都不是，请参考上面提到的 moshen zare 视频。

## 许可证

### 此插件采用 MIT 许可证。您可以以任何方式使用或更改此软件。不需要署名，但我们将不胜感激。

## 支持
请给此仓库点星标，并与其他也会从此插件中受益的开发者分享！