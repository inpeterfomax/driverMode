


static struct v4l2_subdev *msm_sd_find(const char *name)
{
    unsigned long flags;
    struct v4l2_subdev *subdev = NULL;
    struct v4l2_subdev *subdev_out = NULL;

    spin_lock_irqsave(&msm_v4l2_dev->lock,flags);
    if (!list_empty(&msm_v4l2_dev->subdevs)) {
        list_for_each_entry(subdev, &msm_v4l2_dev->subdevs, list)       //list_for_each_entry ;;
            if (!strcmp(name, subdev->name)) {
                subdev_out = subdev;
                break;
            }
    }
    spin_unlock_irqstore(&msm_v4l2_dev->lock);
}
