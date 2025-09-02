**除了列出的方法和属性外，每个属性还具有设置器和获取器函数，格式如下：**
 `set_propertyname()`, `get_propertyname()`（单词间用下划线分隔）

### @ Spawner ![Spawner](https://github.com/Moonzel/Godot-PerfBullets/assets/96361809/ae8e9811-520f-4e99-a0cc-1b5c2e6c2598)

#### 插件的主要类。这是管理子弹生成和每帧移动的基础类。在这里，您可以控制子弹的几乎所有属性，包括旋转、追踪、动画、重力等。它还包含选择节点启动方式以及运行所使用的进程的选项。

<details>
<summary>方法</summary>
<br>
	
- `void _main(float delta)`：每帧运行的函数，根据 `spawnerMode` 在 `_process` 函数或 `_physics_process` 函数中运行。此函数最大，包含以下逻辑：生成新子弹、如果没有活动子弹则自动删除节点、设置旋转（虽然不是直接设置，参见 `startRotation`）、更新旋转、移动子弹、检查碰撞、检查子弹是否超出边界（BulletBorder）以及检查子弹是否达到 `maxLifetime`。它是插件的主要函数。
- `void start_node(String nme)`：节点启动时运行的函数，可以在运行时（`ONSTART`）或 PatternManager 发出信号时（`PATTERNMANAGER`）运行。它设置网格的缩放、设置 `startRotation`，并将多网格重置为正确的属性（instance_count、custom_data、visible_instance_count），为池中的每个子弹创建一个 BulProps 资源，设置动画的着色器参数，并为节点创建一个计时器以在正确的间隔（`fireRate`）生成子弹。
- `void spawn_bullet_self(Vector2 dir)`：生成一颗子弹。它接受方向参数，在 `_main` 函数中设置。它获取下一个非活动索引，并设置子弹的所有初始属性。如果形状上还没有形状，它还会向 `BulProps` 资源添加一个形状。最后，它将子弹在主数组中的索引添加到另一个数组中，以便在 `_main` 函数中仅迭代活动子弹。
- `void clear_all()`：将生成器中的所有子弹返回到池中。
- `void free_bullet_to_pool(int idx)`：接受子弹的索引。它将子弹设置为不可见，将其属性恢复为默认值，并将其从可见子弹数组中移除。
- `int get_next_idx()`：迭代主 `bullets` 数组中的子弹，直到找到非活动子弹。然后返回索引，以便在 `spawn_bullet_self` 中生成子弹。
- `void calc_vel(BulProps bul, float delta)`：在 `_main` 函数中每帧运行。向子弹添加 `acceleration`，并确保子弹未达到其 `minSpeed` 或 `maxSpeed`（在 BulletType 中设置）。
- `void _add_shape(BulProps)`：每次生成尚未包含碰撞形状的子弹时运行。它查看 BulletType 的碰撞形状并复制一份以供子弹使用。这样做是为了避免 RID 混淆。
- `void animate(BulProps, int num, float delta)`：每帧移动自定义数据以调整着色器读取的内容，移动 UV 以基于精灵表产生动画。检查行中是否还有更多内容，如果没有，则移动到下一列，如果都没有，则重置为原始值。
- `void set_bounding_box(Rect2 box)`：设置子弹自动返回到池中的边界框。
- `int get_active_bullet()`：用于调试目的。返回一个包含当前屏幕上所有活动子弹的数组。不要在正式环境中使用，因为它可能会影响性能。
- `BulProps get_bullet_from_index(int index)`：返回给定索引处的子弹。可用于获取特定子弹的信息或手动设置子弹的信息。

</details>

<details>
<summary>属性</summary>
<br>

- `bulletType`：创建 BulletType 资源的属性。这控制子弹的各种属性（参考 BulletType）。
- `bulletsPerRadius`：每个半径上生成的子弹数量。
- `columnsInAtlas`：精灵表中的列数（用于动画）。
- `degreesBetweenRadii`：如果创建了多个半径，这将是它们之间的偏移量。可用于创建具有多个方向的更复杂模式。
- `fireRadiusDegrees`：半径的大小（以度为单位）。例如，值为 90 将在 90 度空间内等间距生成子弹。
- `fireRate`：子弹生成之间的秒数。
- `gravity`：添加到子弹速度的重力量。可以是正数或负数。
- `homing`：子弹是否应追踪 `trackedNode` 属性中的 Node2D。
- `homingWeight`：追踪的权重。数字越大，锁定追踪节点方向的速度越快。
- `ID`：用于通过 PatternManager 激活特定生成器的数字。
- `maxSpin`：生成器可以旋转的最大量，它要么达到该值，要么重新开始并向另一个方向旋转（参见 restartAtSpin）。
- `minSpin`：生成器可以旋转的最小量，它要么达到该值，要么重新开始并向另一个方向旋转（参见 restartAtSpin）。
- `moveWithParent`：生成器是否随父节点移动。如果为 `false`，生成器将保持静止；如果为 `true`，它将随父节点改变位置。（这将一起移动所有子弹，因为它们不是场景中的子节点）。
- `numberOfRadii`：半径的数量。通常应设置为 1，但可以使用此属性创建更复杂的模式。
- `numberOfShots`：生成器生成完整射击的次数，设置为 -1 以无限射击。
- `offsetTowardPlayer`：半径相对于 `trackedNode` 的偏移量。这样，一旦选择 `startTowardPlayer` 或 `staysTowardPlayer`，您可以控制生成器的中点是否在 `trackedNode` 或末端。
- `poolCount`：池中的子弹数量。实例化后无法更改，否则会发生错误（这是由于 MultiMesh 的工作方式）。如果池中没有足够的子弹，游戏将崩溃，因此请确保池中有足够的子弹。
- `randomRadius`：如果选择了 `randomStart`，这将控制随机子弹的射击半径。
- `randomStart`：获取 `poolCount` 中的子弹数量并以随机方向射击。每次都会完全随机。可以使用 `randomRadius` 以特定方向射击。
- `restartAtSpin`：如果 `spinAcceleration` 不为 0，当旋转值达到 `maxSpin` 或 `minSpin` 时，`spinAcceleration` 将开始向相反方向作用，创建漂亮的模式。
- `returnBulletsToPoolAutomatically`：子弹碰撞后是否自动返回到池中。如果计划使用 `bullet_hit` 信号中的子弹数据，请勿使用此选项。
- `rowsInAtlas`：精灵表中的行数（用于动画）。
- `spawnerMode`：可以是 PHYSICS 或 PROCESS。PHYSICS 使用 `_physics_process` 进行所有计算，PROCESS 使用 `_process` 进行所有计算。
- `spinAcceleration`：每帧添加到旋转的量。可以是负数或正数。
- `spinRate`：旋转的起始量。可以由 `spinAcceleration` 修改。
- `startMode`：可以是 `ONSTART` 或 `PATTERNMANAGER`。节点在启动前不会运行任何内容。`ONSTART` 在节点添加到树中时立即启动，`PATTERNMANAGER` 在 PatternManager 中的计时器超时时启动节点。
- `startRotation`：生成器开始的旋转角度（以度为单位）。这是一个用于计算的任意数字，您不应编辑生成器节点的实际旋转。
- `startTowardPlayer`：生成器节点的起始旋转设置为朝向 `targetNode`。这是自动设置的，可以使用 `offsetTowardPlayer` 添加偏移量。
- `staysTowardPlayer`：生成器节点的旋转不断更改为朝向 `targetNode`。这是自动设置的，可以使用 `offsetTowardPlayer` 添加偏移量。
- `textureRotation`：仅应用于纹理的旋转角度（以度为单位）。
- `trackedNode`：用于追踪功能的 Node2D。可以是任何继承自 Node2D 类的节点类型。

</details>

<details>
<summary>信号</summary>
<br>

- `bullet_hit`：一个重要信号。返回三件事：结果数组、子弹的索引和生成器。可用于控制子弹被击中时的各种方面。如果 `returnBulletsToPoolAutomatically` 为 false，可以在此处完成（`spawner.free_bullet_to_pool(bulletIndex)`）。也可以在此处生成不同的场景，例如另一种类型的子弹。可能有一个 Area2D，当子弹与其碰撞时，某些属性会更改。（参见基本设置步骤 14 以了解此信号的另一种应用）。

</details>

### @ BulletType ![BulletType](https://github.com/Moonzel/Godot-PerfBullets/assets/96361809/711d80b6-13c0-4008-ba4d-847d1cb5edc8)

#### 用于生成器的 `Bullet Type` 属性的资源。这决定了该生成器中生成的子弹的某些关键属性，并且由于它是一个资源，您可以将资源保存为特定类型的子弹，并使用其他使用该资源的生成器。生成器中的每个子弹共享这些属性。尽量不要在运行时编辑这些设置，因为许多设置是在生成器添加到树中时一次性设置的。

<details>
<summary>属性</summary>
<br>
	
- `acceleration`：每帧添加到每个子弹速度的值，随时间增加或减少速度。
- `animationSpeed`：帧之间切换的速度（以秒为单位）。每次 `animationSpeed` 时间过去时，除非只有一帧，否则子弹上的帧会切换。
- `collideWithAreas`：子弹是否可以与物理体碰撞。
- `collideWithBodies`：子弹是否可以与 area2ds 碰撞。
- `initialSpeed`：每个子弹开始的初始速度。
- `mask`：控制子弹检查哪些层的碰撞遮罩。
- `maxLifetime`：子弹在自动返回到子弹池（`free_to_bullet_pool`）之前的最大生命周期。
- `maxSpeed`：子弹可以达到的最大速度（使用加速度时），在停止增加或减少（取决于加速度的方向）之前。
- `minSpeed`：子弹可以达到的最小速度（使用加速度时），在停止增加或减少（取决于加速度的方向）之前。
- `scale`：用于子弹的图像的缩放。不缩放碰撞形状。
- `numberOfQueries`：每帧进行的物理查询次数。出于性能原因，最好保持为 1，但如果需要更多，此选项可用。

</details>

### @ BulletBorder ![BulletBorder](https://github.com/Moonzel/Godot-PerfBullets/assets/96361809/a3392bf8-b281-4463-b9ce-aa82de0c431d)

#### 一个使用两个 Node2D 设置矩形边界的类。当子弹穿过边界时，它将子弹返回到池中并停用它们。在编辑器中，您可以放置这些 Node2D 来指定矩形。建议将它们放置在屏幕外，以便玩家看不到子弹消失。

<details>
<summary>属性</summary>
<br>

- `topLeft`：一个 Node2D，其位置用于确定表示 BulletBorder 的矩形的左上角位置。
- `bottomRight`：一个 Node2D，其位置用于确定表示 BulletBorder 的矩形的右下角位置。
- `boundaryRect`：使用 `TopLeft` 和 `BottomRight` 构建的 Rect2。

</details>

<details>
<summary>方法</summary>
<br>

- `void update_boundary_rect()`：在 BulletBorder 的 `_ready` 函数中自动运行一次，但可以根据需要经常运行。它设置生成器的 `boundry_rect`（内部），以便子弹在穿过矩形时运行 `free_bullet_to_pool`。

</details>

### @ PatternManager ![PatternManager](https://github.com/Moonzel/Godot-PerfBullets/assets/96361809/3c8d1c62-26f8-4402-a6d3-0e81934fb8c6)

#### 此节点设置为控制每个节点发射时间的位置，通常放置在场景中与生成器相同的级别。当您向场景添加生成器时，可以向 PatternManager 添加一个相应的计时器节点作为子节点。当此计时器超时时，它将发送一个带有其名称（也应该是生成器的确切名称）的信号，并激活它。您可以选择使用 PatternManager 方法或在要使用节点时实例化它们（`ONSTART`）。

<details>
<summary>属性</summary>
<br>

- `data`：一个数组，每个生成器对应一个 PatternSpawnerData。它根据 PatternSpawnerData 的 time、ID 和 timerMode 属性指定每个生成器何时生成。

</details>

<details>
<summary>方法</summary>
<br>

- `find_spawners(startingNode: Node) -> Array`：接受一个节点开始搜索（通常是 PatternManager 的父节点），并递归查找父节点下的每个生成器节点。然后将其添加到数组中以设置 PatternManager 的其余部分。

</details>

<details>
<summary>信号</summary>
<br>

- `start`：接受节点的名称。在计时器超时后激活每个生成器。计时器的名称必须是生成器的确切名称才能工作。

</details>

### @ BulProps ![BulProps](https://github.com/Moonzel/Godot-PerfBullets/assets/96361809/c7f5f0ac-517b-4cdf-8906-8563a0da4867)

#### 与每个生成的子弹关联的资源。它主要在 Spawner 类内部使用。可以直接编辑，但只能通过 `get_bullet_from_index()` 进行。

<details>
<summary>属性</summary>
<br>

- `position`：子弹的局部位置（相对于其生成器节点）。
- `direction`：描述子弹行进方向的 Vector2。
- `speed`：乘以方向以产生子弹速度的量。
- `lifetime`：子弹已激活的时间量。每次重新添加到池时重置。每帧按 delta 递增。
- `animationTime`：每个动画间隔之间经过的时间量（以秒为单位）（每帧更改之间的时间）。
- `shapeRID`：与用于检测碰撞的形状关联的唯一 RID。未附加到任何节点或 PhysicsBody，所有碰撞计算均通过生成器完成。

</details>

### @ PatternSpawnerData ![PatternSpawnerData](https://github.com/Moonzel/Godot-PerfBullets/assets/96361809/466f3252-5434-4977-83b4-9bc8ad571b2e)

#### 这是一个由 PatternManager 使用的资源，用于保存哪些生成器应在何时激活的数据。

<details>
<summary>属性</summary>
<br>

- `ID`：生成器的 `ID`，以便在场景树中找到它。
- `time`：生成器激活前的等待时间（以秒为单位）。
- `timerMode`：可以是 Physics（物理）或 Idle（空闲）。它决定计时器运行的模式。

</details>

### @ PerfBulletsAnimation 着色器

#### 这是在后台用于使动画与 MultiMeshInstance2D 配合工作的着色器。建议不要过多更改此着色器，但如果需要为子弹添加额外效果，请将它们与此着色器结合使用。此着色器是生成器正常工作所必需的，否则会导致崩溃。

<details>
<summary>属性</summary>
<br>

- `col`：根据生成器节点的 `columnsInAtlas` 属性在运行时设置。通常无需手动编辑此属性。
- `row`：根据生成器节点的 `rowsInAtlas` 属性在运行时设置。通常无需手动编辑此属性。
- `custom`：这是一个在顶点着色器中设置的 varying vec4。它获取 `INSTANCE_CUSTOM` 属性并将其应用于 `custom`，以便在片段着色器中使用。自定义数据的格式如下（子弹的可见性（0.0 或 1.0）、offsetx（用于产生动画的 x 轴偏移）、offsety（用于产生动画的 y 轴偏移））。

</details>