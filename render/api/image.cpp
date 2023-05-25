#include "image.hpp"

as::Image::Image(const vk::ImageCreateInfo& image_info, const vma::AllocationCreateInfo& alloc_info)
{
    vma::AllocationInfo finish_info{};
    auto result = device_->allocator_.createImage(image_info, alloc_info, finish_info);
    sset(*this, result.first, result.second, finish_info.deviceMemory);
}

as::Image::Image(const vk::ImageCreateInfo& image_info, const vma::AllocationCreateInfo& alloc_info,
                 vk::ImageViewCreateInfo view_info)
    : Image(image_info, alloc_info)
{
    create_image_view(view_info);
}

as::Image::~Image()
{
    if (VkImageView(*this) != VK_NULL_HANDLE)
    {
        device_->destroyImageView(*this);
    }
    device_->allocator_.destroyImage(*this, *this);
}

void as::Image::create_image_view(vk::ImageViewCreateInfo view_info)
{
    view_info.image = *this;
    sset(*this, device_->createImageView(view_info));
}

void as::Image::destroy_image_view()
{
    device_->destroyImageView(*this);
    casts(vk::ImageView&, *this) = VK_NULL_HANDLE;
}

as::SwapchainImage::SwapchainImage(vk::Image& vk_image, vk::Format format)
    : vk::Image(vk_image)
{
    vk::ImageViewCreateInfo create_info{};
    create_info.image = vk_image;
    create_info.viewType = vk::ImageViewType::e2D;
    create_info.format = format;

    create_info.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
    create_info.subresourceRange.baseMipLevel = 0;
    create_info.subresourceRange.levelCount = 1;
    create_info.subresourceRange.baseArrayLayer = 0;
    create_info.subresourceRange.layerCount = 1;

    sset(*this, device_->createImageView(create_info));
}

as::SwapchainImage::~SwapchainImage()
{
    device_->destroyImageView(*this);
}

as::ImageAttachment::ImageAttachment(const vk::ImageCreateInfo& image_info, const vma::AllocationCreateInfo& alloc_info)
    : Image(image_info, alloc_info)
{
}

as::ImageAttachment::ImageAttachment(const vk::ImageCreateInfo& image_info, const vma::AllocationCreateInfo& alloc_info,
                                     vk::ImageViewCreateInfo view_info)
    : Image(image_info, alloc_info, view_info)
{
}
