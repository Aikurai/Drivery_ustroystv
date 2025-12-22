#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>

#define DRIVER_NAME "maipractice5driver"

static struct net_device *dev;

static netdev_tx_t ndo_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	uint8_t *data = skb->data;
	uint32_t i;

	printk(KERN_INFO "%s xmit\n", DRIVER_NAME);
	printk(KERN_INFO "%s %p struct skbuff\n", DRIVER_NAME, (void *)skb);
	printk(KERN_INFO "%s Packet info - Len %u, Head %p, Data %p, Tail %u, End %u\n",
		DRIVER_NAME, skb->len, (void *)skb->head, (void *)skb->data, skb->tail, skb->end);
	printk(KERN_INFO "%s First %u bytes\n", DRIVER_NAME, skb->len);
	
	printk(KERN_INFO "%s Hex ", DRIVER_NAME);
	for (i = 0; i < skb->len; i++)
		printk(KERN_CONT "%02x ", data[i]);
	printk(KERN_CONT "\n");
	
	printk(KERN_INFO "%s Hex ", DRIVER_NAME);
	for (i = 0; i < skb->len; i++)
		printk(KERN_CONT "%c ", data[i]);
	printk(KERN_CONT "\n");

	dev_kfree_skb(skb);
	return NETDEV_TX_OK;
}

static const struct net_device_ops fake_net_ops = {
	.ndo_start_xmit = ndo_start_xmit,
};

static int __init fake_net_init(void)
{
	dev = alloc_netdev(0, "practice5", NET_NAME_UNKNOWN, ether_setup);
	if (!dev)
		return -ENOMEM;

	dev->netdev_ops = &fake_net_ops;
	
	if (register_netdev(dev)) {
		free_netdev(dev);
		return -ENODEV;
	}

	printk(KERN_INFO "%s initialized\n", DRIVER_NAME);
	return 0;
}

static void __exit fake_net_exit(void)
{
	unregister_netdev(dev);
	free_netdev(dev);
	printk(KERN_INFO "%s removed\n", DRIVER_NAME);
}

module_init(fake_net_init);
module_exit(fake_net_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MAI");
MODULE_DESCRIPTION("Fake network driver");
