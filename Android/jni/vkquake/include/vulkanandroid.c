/*
* Android Vulkan function pointer loader
*
* Copyright (C) 2016 by Sascha Willems - www.saschawillems.de
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#include "vulkanandroid.h"

#if defined(__ANDROID__)
	#include <android/log.h>
	#include <dlfcn.h>

PFN_vkCreateInstance vkCreateInstance;
PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr;
PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
PFN_vkCreateDevice vkCreateDevice;
PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices;
PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties;
PFN_vkEnumerateDeviceExtensionProperties vkEnumerateDeviceExtensionProperties;
PFN_vkEnumerateDeviceLayerProperties vkEnumerateDeviceLayerProperties;
PFN_vkGetPhysicalDeviceFormatProperties vkGetPhysicalDeviceFormatProperties;
PFN_vkGetPhysicalDeviceFeatures vkGetPhysicalDeviceFeatures;
PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties;
PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties;
PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties;
PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties;
PFN_vkCmdPipelineBarrier vkCmdPipelineBarrier;
PFN_vkCreateShaderModule vkCreateShaderModule;
PFN_vkCreateBuffer vkCreateBuffer;
PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements;
PFN_vkMapMemory vkMapMemory;
PFN_vkUnmapMemory vkUnmapMemory;
PFN_vkFlushMappedMemoryRanges vkFlushMappedMemoryRanges;
PFN_vkBindBufferMemory vkBindBufferMemory;
PFN_vkDestroyBuffer vkDestroyBuffer;
PFN_vkAllocateMemory vkAllocateMemory;
PFN_vkBindImageMemory vkBindImageMemory;
PFN_vkGetImageSubresourceLayout vkGetImageSubresourceLayout;
PFN_vkCmdCopyBuffer vkCmdCopyBuffer;
PFN_vkCmdCopyBufferToImage vkCmdCopyBufferToImage;
PFN_vkCmdCopyImage vkCmdCopyImage;
PFN_vkCmdBlitImage vkCmdBlitImage;
PFN_vkCmdClearAttachments vkCmdClearAttachments;
PFN_vkCreateSampler vkCreateSampler;
PFN_vkDestroySampler vkDestroySampler;
PFN_vkDestroyImage vkDestroyImage;
PFN_vkFreeMemory vkFreeMemory;
PFN_vkCreateRenderPass vkCreateRenderPass;
PFN_vkCmdBeginRenderPass vkCmdBeginRenderPass;
PFN_vkCmdNextSubpass vkCmdNextSubpass;
PFN_vkCmdEndRenderPass vkCmdEndRenderPass;
PFN_vkCmdExecuteCommands vkCmdExecuteCommands;
PFN_vkCreateImage vkCreateImage;
PFN_vkGetImageMemoryRequirements vkGetImageMemoryRequirements;
PFN_vkCreateImageView vkCreateImageView;
PFN_vkDestroyImageView vkDestroyImageView;
PFN_vkCreateSemaphore vkCreateSemaphore;
PFN_vkDestroySemaphore vkDestroySemaphore;
PFN_vkCreateFence vkCreateFence;
PFN_vkDestroyFence vkDestroyFence;
PFN_vkWaitForFences vkWaitForFences;
PFN_vkResetFences vkResetFences;
PFN_vkCreateCommandPool vkCreateCommandPool;
PFN_vkDestroyCommandPool vkDestroyCommandPool;
PFN_vkAllocateCommandBuffers vkAllocateCommandBuffers;
PFN_vkBeginCommandBuffer vkBeginCommandBuffer;
PFN_vkEndCommandBuffer vkEndCommandBuffer;
PFN_vkGetDeviceQueue vkGetDeviceQueue;
PFN_vkQueueSubmit vkQueueSubmit;
PFN_vkQueueWaitIdle vkQueueWaitIdle;
PFN_vkDeviceWaitIdle vkDeviceWaitIdle;
PFN_vkCreateFramebuffer vkCreateFramebuffer;
PFN_vkCreatePipelineCache vkCreatePipelineCache;
PFN_vkCreatePipelineLayout vkCreatePipelineLayout;
PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines;
PFN_vkCreateComputePipelines vkCreateComputePipelines;
PFN_vkCreateDescriptorPool vkCreateDescriptorPool;
PFN_vkCreateDescriptorSetLayout vkCreateDescriptorSetLayout;
PFN_vkAllocateDescriptorSets vkAllocateDescriptorSets;
PFN_vkFreeDescriptorSets vkFreeDescriptorSets;
PFN_vkUpdateDescriptorSets vkUpdateDescriptorSets;
PFN_vkCmdBindDescriptorSets vkCmdBindDescriptorSets;
PFN_vkCmdBindPipeline vkCmdBindPipeline;
PFN_vkCmdBindVertexBuffers vkCmdBindVertexBuffers;
PFN_vkCmdBindIndexBuffer vkCmdBindIndexBuffer;
PFN_vkCmdSetViewport vkCmdSetViewport;
PFN_vkCmdSetScissor vkCmdSetScissor;
PFN_vkCmdSetLineWidth vkCmdSetLineWidth;
PFN_vkCmdSetDepthBias vkCmdSetDepthBias;
PFN_vkCmdPushConstants vkCmdPushConstants;
PFN_vkCmdDrawIndexed vkCmdDrawIndexed;
PFN_vkCmdDraw vkCmdDraw;
PFN_vkCmdDispatch vkCmdDispatch;
PFN_vkDestroyPipeline vkDestroyPipeline;
PFN_vkDestroyPipelineLayout vkDestroyPipelineLayout;
PFN_vkDestroyDescriptorSetLayout vkDestroyDescriptorSetLayout;
PFN_vkDestroyDevice vkDestroyDevice;
PFN_vkDestroyInstance vkDestroyInstance;
PFN_vkDestroyDescriptorPool vkDestroyDescriptorPool;
PFN_vkFreeCommandBuffers vkFreeCommandBuffers;
PFN_vkDestroyRenderPass vkDestroyRenderPass;
PFN_vkDestroyFramebuffer vkDestroyFramebuffer;
PFN_vkDestroyShaderModule vkDestroyShaderModule;
PFN_vkDestroyPipelineCache vkDestroyPipelineCache;
PFN_vkCreateQueryPool vkCreateQueryPool;
PFN_vkDestroyQueryPool vkDestroyQueryPool;
PFN_vkGetQueryPoolResults vkGetQueryPoolResults;
PFN_vkCmdBeginQuery vkCmdBeginQuery;
PFN_vkCmdEndQuery vkCmdEndQuery;
PFN_vkCmdResetQueryPool vkCmdResetQueryPool;
PFN_vkCmdCopyQueryPoolResults vkCmdCopyQueryPoolResults;

PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR;
PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR;

void *libVulkan;

// Dynamically load Vulkan library and base function pointers
bool loadVulkanLibrary()
{
	__android_log_print(ANDROID_LOG_INFO, "vulkanandroid", "Loading libvulkan.so...\n");

	// Load vulkan library
	libVulkan = dlopen("libvulkan.so", RTLD_NOW | RTLD_LOCAL);
	if (!libVulkan)
	{
		__android_log_print(ANDROID_LOG_INFO, "vulkanandroid", "Could not load vulkan library : %s!\n", dlerror());
		return false;
	}

	// Load base function pointers
	vkEnumerateInstanceExtensionProperties = (PFN_vkEnumerateInstanceExtensionProperties)(dlsym(libVulkan, "vkEnumerateInstanceExtensionProperties"));
	vkEnumerateInstanceLayerProperties = (PFN_vkEnumerateInstanceLayerProperties)(dlsym(libVulkan, "vkEnumerateInstanceLayerProperties"));
	vkCreateInstance = (PFN_vkCreateInstance)(dlsym(libVulkan, "vkCreateInstance"));
	vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)(dlsym(libVulkan, "vkGetInstanceProcAddr"));
	vkGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr)(dlsym(libVulkan, "vkGetDeviceProcAddr"));

	return true;
}

// Load instance based Vulkan function pointers
void loadVulkanFunctions(VkInstance instance)
{
	__android_log_print(ANDROID_LOG_INFO, "vkQuake", "Loading instance based function pointers...");

	vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices)(vkGetInstanceProcAddr(instance, "vkEnumeratePhysicalDevices"));
	vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties)(vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceProperties"));
	vkEnumerateDeviceLayerProperties = (PFN_vkEnumerateDeviceLayerProperties)(vkGetInstanceProcAddr(instance, "vkEnumerateDeviceLayerProperties"));
	vkEnumerateDeviceExtensionProperties = (PFN_vkEnumerateDeviceExtensionProperties)(vkGetInstanceProcAddr(instance, "vkEnumerateDeviceExtensionProperties"));
	vkGetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties)(vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceQueueFamilyProperties"));
	vkGetPhysicalDeviceFeatures = (PFN_vkGetPhysicalDeviceFeatures)(vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceFeatures"));
	vkCreateDevice = (PFN_vkCreateDevice)(vkGetInstanceProcAddr(instance, "vkCreateDevice"));
	vkGetPhysicalDeviceFormatProperties = (PFN_vkGetPhysicalDeviceFormatProperties)(vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceFormatProperties"));
	vkGetPhysicalDeviceMemoryProperties = (PFN_vkGetPhysicalDeviceMemoryProperties)(vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceMemoryProperties"));

	vkCmdPipelineBarrier = (PFN_vkCmdPipelineBarrier)(vkGetInstanceProcAddr(instance, "vkCmdPipelineBarrier"));
	vkCreateShaderModule = (PFN_vkCreateShaderModule)(vkGetInstanceProcAddr(instance, "vkCreateShaderModule"));

	vkCreateBuffer = (PFN_vkCreateBuffer)(vkGetInstanceProcAddr(instance, "vkCreateBuffer"));
	vkGetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements)(vkGetInstanceProcAddr(instance, "vkGetBufferMemoryRequirements"));
	vkMapMemory = (PFN_vkMapMemory)(vkGetInstanceProcAddr(instance, "vkMapMemory"));
	vkUnmapMemory = (PFN_vkUnmapMemory)(vkGetInstanceProcAddr(instance, "vkUnmapMemory"));
	vkFlushMappedMemoryRanges = (PFN_vkFlushMappedMemoryRanges)(vkGetInstanceProcAddr(instance, "vkFlushMappedMemoryRanges"));
	vkBindBufferMemory = (PFN_vkBindBufferMemory)(vkGetInstanceProcAddr(instance, "vkBindBufferMemory"));
	vkDestroyBuffer = (PFN_vkDestroyBuffer)(vkGetInstanceProcAddr(instance, "vkDestroyBuffer"));

	vkAllocateMemory = (PFN_vkAllocateMemory)(vkGetInstanceProcAddr(instance, "vkAllocateMemory"));
	vkFreeMemory = (PFN_vkFreeMemory)(vkGetInstanceProcAddr(instance, "vkFreeMemory"));
	vkCreateRenderPass = (PFN_vkCreateRenderPass)(vkGetInstanceProcAddr(instance, "vkCreateRenderPass"));
	vkCmdBeginRenderPass = (PFN_vkCmdBeginRenderPass)(vkGetInstanceProcAddr(instance, "vkCmdBeginRenderPass"));
	vkCmdNextSubpass = (PFN_vkCmdNextSubpass)(vkGetInstanceProcAddr(instance, "vkCmdNextSubpass"));
	vkCmdEndRenderPass = (PFN_vkCmdEndRenderPass)(vkGetInstanceProcAddr(instance, "vkCmdEndRenderPass"));
	vkCmdExecuteCommands = (PFN_vkCmdExecuteCommands)(vkGetInstanceProcAddr(instance, "vkCmdExecuteCommands"));

	vkCreateImage = (PFN_vkCreateImage)(vkGetInstanceProcAddr(instance, "vkCreateImage"));
	vkGetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements)(vkGetInstanceProcAddr(instance, "vkGetImageMemoryRequirements"));
	vkCreateImageView = (PFN_vkCreateImageView)(vkGetInstanceProcAddr(instance, "vkCreateImageView"));
	vkDestroyImageView = (PFN_vkDestroyImageView)(vkGetInstanceProcAddr(instance, "vkDestroyImageView"));
	vkBindImageMemory = (PFN_vkBindImageMemory)(vkGetInstanceProcAddr(instance, "vkBindImageMemory"));
	vkGetImageSubresourceLayout = (PFN_vkGetImageSubresourceLayout)(vkGetInstanceProcAddr(instance, "vkGetImageSubresourceLayout"));
	vkCmdCopyImage = (PFN_vkCmdCopyImage)(vkGetInstanceProcAddr(instance, "vkCmdCopyImage"));
	vkCmdBlitImage = (PFN_vkCmdBlitImage)(vkGetInstanceProcAddr(instance, "vkCmdBlitImage"));
	vkDestroyImage = (PFN_vkDestroyImage)(vkGetInstanceProcAddr(instance, "vkDestroyImage"));

	vkCmdClearAttachments = (PFN_vkCmdClearAttachments)(vkGetInstanceProcAddr(instance, "vkCmdClearAttachments"));

	vkCmdCopyBuffer = (PFN_vkCmdCopyBuffer)(vkGetInstanceProcAddr(instance, "vkCmdCopyBuffer"));
	vkCmdCopyBufferToImage = (PFN_vkCmdCopyBufferToImage)(vkGetInstanceProcAddr(instance, "vkCmdCopyBufferToImage"));

	vkCreateSampler = (PFN_vkCreateSampler)(vkGetInstanceProcAddr(instance, "vkCreateSampler"));
	vkDestroySampler = (PFN_vkDestroySampler)(vkGetInstanceProcAddr(instance, "vkDestroySampler"));;

	vkCreateSemaphore = (PFN_vkCreateSemaphore)(vkGetInstanceProcAddr(instance, "vkCreateSemaphore"));
	vkDestroySemaphore = (PFN_vkDestroySemaphore)(vkGetInstanceProcAddr(instance, "vkDestroySemaphore"));

	vkCreateFence = (PFN_vkCreateFence)(vkGetInstanceProcAddr(instance, "vkCreateFence"));
	vkDestroyFence = (PFN_vkDestroyFence)(vkGetInstanceProcAddr(instance, "vkDestroyFence"));
	vkWaitForFences = (PFN_vkWaitForFences)(vkGetInstanceProcAddr(instance, "vkWaitForFences"));
	vkResetFences = (PFN_vkResetFences)(vkGetInstanceProcAddr(instance, "vkResetFences"));;

	vkCreateCommandPool = (PFN_vkCreateCommandPool)(vkGetInstanceProcAddr(instance, "vkCreateCommandPool"));
	vkDestroyCommandPool = (PFN_vkDestroyCommandPool)(vkGetInstanceProcAddr(instance, "vkDestroyCommandPool"));;

	vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers)(vkGetInstanceProcAddr(instance, "vkAllocateCommandBuffers"));
	vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer)(vkGetInstanceProcAddr(instance, "vkBeginCommandBuffer"));
	vkEndCommandBuffer = (PFN_vkEndCommandBuffer)(vkGetInstanceProcAddr(instance, "vkEndCommandBuffer"));

	vkGetDeviceQueue = (PFN_vkGetDeviceQueue)(vkGetInstanceProcAddr(instance, "vkGetDeviceQueue"));
	vkQueueSubmit = (PFN_vkQueueSubmit)(vkGetInstanceProcAddr(instance, "vkQueueSubmit"));
	vkQueueWaitIdle = (PFN_vkQueueWaitIdle)(vkGetInstanceProcAddr(instance, "vkQueueWaitIdle"));

	vkDeviceWaitIdle = (PFN_vkDeviceWaitIdle)(vkGetInstanceProcAddr(instance, "vkDeviceWaitIdle"));

	vkCreateFramebuffer = (PFN_vkCreateFramebuffer)(vkGetInstanceProcAddr(instance, "vkCreateFramebuffer"));

	vkCreatePipelineCache = (PFN_vkCreatePipelineCache)(vkGetInstanceProcAddr(instance, "vkCreatePipelineCache"));
	vkCreatePipelineLayout = (PFN_vkCreatePipelineLayout)(vkGetInstanceProcAddr(instance, "vkCreatePipelineLayout"));
	vkCreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines)(vkGetInstanceProcAddr(instance, "vkCreateGraphicsPipelines"));
	vkCreateComputePipelines = (PFN_vkCreateComputePipelines)(vkGetInstanceProcAddr(instance, "vkCreateComputePipelines"));

	vkCreateDescriptorPool = (PFN_vkCreateDescriptorPool)(vkGetInstanceProcAddr(instance, "vkCreateDescriptorPool"));
	vkCreateDescriptorSetLayout = (PFN_vkCreateDescriptorSetLayout)(vkGetInstanceProcAddr(instance, "vkCreateDescriptorSetLayout"));

	vkAllocateDescriptorSets = (PFN_vkAllocateDescriptorSets)(vkGetInstanceProcAddr(instance, "vkAllocateDescriptorSets"));
	vkFreeDescriptorSets = (PFN_vkFreeDescriptorSets)(vkGetInstanceProcAddr(instance, "vkFreeDescriptorSets"));
	vkUpdateDescriptorSets = (PFN_vkUpdateDescriptorSets)(vkGetInstanceProcAddr(instance, "vkUpdateDescriptorSets"));

	vkCmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets)(vkGetInstanceProcAddr(instance, "vkCmdBindDescriptorSets"));
	vkCmdBindPipeline = (PFN_vkCmdBindPipeline)(vkGetInstanceProcAddr(instance, "vkCmdBindPipeline"));
	vkCmdBindVertexBuffers = (PFN_vkCmdBindVertexBuffers)(vkGetInstanceProcAddr(instance, "vkCmdBindVertexBuffers"));
	vkCmdBindIndexBuffer = (PFN_vkCmdBindIndexBuffer)(vkGetInstanceProcAddr(instance, "vkCmdBindIndexBuffer"));

	vkCmdSetViewport = (PFN_vkCmdSetViewport)(vkGetInstanceProcAddr(instance, "vkCmdSetViewport"));
	vkCmdSetScissor = (PFN_vkCmdSetScissor)(vkGetInstanceProcAddr(instance, "vkCmdSetScissor"));
	vkCmdSetLineWidth = (PFN_vkCmdSetLineWidth)(vkGetInstanceProcAddr(instance, "vkCmdSetLineWidth"));
	vkCmdSetDepthBias = (PFN_vkCmdSetDepthBias)(vkGetInstanceProcAddr(instance, "vkCmdSetDepthBias"));
	vkCmdPushConstants = (PFN_vkCmdPushConstants)(vkGetInstanceProcAddr(instance, "vkCmdPushConstants"));;

	vkCmdDrawIndexed = (PFN_vkCmdDrawIndexed)(vkGetInstanceProcAddr(instance, "vkCmdDrawIndexed"));
	vkCmdDraw = (PFN_vkCmdDraw)(vkGetInstanceProcAddr(instance, "vkCmdDraw"));
	vkCmdDispatch = (PFN_vkCmdDispatch)(vkGetInstanceProcAddr(instance, "vkCmdDispatch"));

	vkDestroyPipeline = (PFN_vkDestroyPipeline)(vkGetInstanceProcAddr(instance, "vkDestroyPipeline"));
	vkDestroyPipelineLayout = (PFN_vkDestroyPipelineLayout)(vkGetInstanceProcAddr(instance, "vkDestroyPipelineLayout"));;
	vkDestroyDescriptorSetLayout = (PFN_vkDestroyDescriptorSetLayout)(vkGetInstanceProcAddr(instance, "vkDestroyDescriptorSetLayout"));
	vkDestroyDevice = (PFN_vkDestroyDevice)(vkGetInstanceProcAddr(instance, "vkDestroyDevice"));
	vkDestroyInstance = (PFN_vkDestroyInstance)(vkGetInstanceProcAddr(instance, "vkDestroyInstance"));
	vkDestroyDescriptorPool = (PFN_vkDestroyDescriptorPool)(vkGetInstanceProcAddr(instance, "vkDestroyDescriptorPool"));
	vkFreeCommandBuffers = (PFN_vkFreeCommandBuffers)(vkGetInstanceProcAddr(instance, "vkFreeCommandBuffers"));
	vkDestroyRenderPass = (PFN_vkDestroyRenderPass)(vkGetInstanceProcAddr(instance, "vkDestroyRenderPass"));
	vkDestroyFramebuffer = (PFN_vkDestroyFramebuffer)(vkGetInstanceProcAddr(instance, "vkDestroyFramebuffer"));
	vkDestroyShaderModule = (PFN_vkDestroyShaderModule)(vkGetInstanceProcAddr(instance, "vkDestroyShaderModule"));
	vkDestroyPipelineCache = (PFN_vkDestroyPipelineCache)(vkGetInstanceProcAddr(instance, "vkDestroyPipelineCache"));

	vkCreateQueryPool = (PFN_vkCreateQueryPool)(vkGetInstanceProcAddr(instance, "vkCreateQueryPool"));
	vkDestroyQueryPool = (PFN_vkDestroyQueryPool)(vkGetInstanceProcAddr(instance, "vkDestroyQueryPool"));
	vkGetQueryPoolResults = (PFN_vkGetQueryPoolResults)(vkGetInstanceProcAddr(instance, "vkGetQueryPoolResults"));

	vkCmdBeginQuery = (PFN_vkCmdBeginQuery)(vkGetInstanceProcAddr(instance, "vkCmdBeginQuery"));
	vkCmdEndQuery = (PFN_vkCmdEndQuery)(vkGetInstanceProcAddr(instance, "vkCmdEndQuery"));
	vkCmdResetQueryPool = (PFN_vkCmdResetQueryPool)(vkGetInstanceProcAddr(instance, "vkCmdResetQueryPool"));
	vkCmdCopyQueryPoolResults = (PFN_vkCmdCopyQueryPoolResults)(vkGetInstanceProcAddr(instance, "vkCmdCopyQueryPoolResults"));

	vkCreateAndroidSurfaceKHR = (PFN_vkCreateAndroidSurfaceKHR)(vkGetInstanceProcAddr(instance, "vkCreateAndroidSurfaceKHR"));
	vkDestroySurfaceKHR = (PFN_vkDestroySurfaceKHR)(vkGetInstanceProcAddr(instance, "vkDestroySurfaceKHR"));

	__android_log_print(ANDROID_LOG_INFO, "vkQuake", "Function pointers loaded");
}

void freeVulkanLibrary()
{
	dlclose(libVulkan);
}

#endif
