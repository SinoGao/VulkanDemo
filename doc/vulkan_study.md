# vulKan学习
文档：
 1. 官方文档：[https://vulkan-tutorial.com/Introduction](https://vulkan-tutorial.com/Introduction);
 2. 中文翻译教程:[https://geek-docs.com/vulkan/vulkan-tutorial/vulkan-tutorial-index.html](https://geek-docs.com/vulkan/vulkan-tutorial/vulkan-tutorial-index.html)
 3. vulKan-hpp:[https://github.com/KhronosGroup/Vulkan-Hpp](https://github.com/KhronosGroup/Vulkan-Hpp);
 4. [SaschaWillems/Vulkan](https://github.com/SaschaWillems/Vulkan) （封装和机构比较好的Vulkan）;

## 一、环境搭建：
开发环境搭建集中在:[vulkan-development-environment-built-on-windows](https://geek-docs.com/vulkan/vulkan-tutorial/vulkan-development-environment-built-on-windows.html)中，配置基本一次就成功;

## 二、基本设置
Vulkan官网对绘图基本流程进行描述，主要分以下步骤：
1. 实例（VKInstance）初始化，物理设备(VkPhysicalDevice)选择，据官网介绍可以选择多块显卡，目前没有看到如何使用；
2. 逻辑设备(VkDevice)创建和队列（图像队列和上屏队列）创建；
3. windows窗口（VKSurfaceKHR）和交换链（VKSwapchainHKR）；
4. 交换链图像(VkImage)，图像视图(VkImageView)和图像缓存（VkFramebuffer）；
5. 渲染通道；
6. 图形管线；
7. 命令缓冲区和命令buffer；

### 2.1 实例创建和物理设备选择
### 2.2 逻辑设备和队列
### 2.3 Surface和交换链
### 2.4 交换链图像、图像视图和图像缓存
### 2.5 渲染通道
### 2.6 管道
### 2.7 命令缓存区和命令buffer


## 三、vulkan中着色细分和SPIR-V：

### 着色器种类有：
1. 顶点着色器（Vertex shaders）；
2. 曲面细分着色器（Tessellation shaders）;
3. 几何着色器(Geometry shaders);
4. 片段着色器(Fragment shaders)；
5. 计算着色器(Compute shaders);
6. ...（如NV mesh_shader,华为subpass shading）;
   
### Vulkan使用着色器为SPIR-V：
SPIR-V介绍:
![SPIR-V](./image/SPIR-V.png)
原文翻译大致意思为：这种二进制格式叫做SPIR-V,他只为Vulkan和OPenCL设计的。这种格式被用来写图形着色器和计算着色器...（来自[Graphics_pipeline_basics](https://vulkan-tutorial.com/Drawing_a_triangle/Graphics_pipeline_basics/Shader_modules)第一段）;

