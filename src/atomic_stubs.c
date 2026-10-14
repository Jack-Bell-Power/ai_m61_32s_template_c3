#include <stdint.h>
#include <stdbool.h>
#include <bflb_irq.h>

// 1-byte 
bool __atomic_compare_exchange_1(volatile void *ptr, void *expected, uint8_t desired, bool weak, int s, int f) {
    uint32_t flags = bflb_irq_save();
    uint8_t val = *(volatile uint8_t *)ptr;
    if (val == *(uint8_t *)expected) {
        *(volatile uint8_t *)ptr = desired;
        bflb_irq_restore(flags);
        return true;
    }
    *(uint8_t *)expected = val;
    bflb_irq_restore(flags);
    return false;
}

// 2-byte
bool __atomic_compare_exchange_2(volatile void *ptr, void *expected, uint16_t desired, bool weak, int s, int f) {
    uint32_t flags = bflb_irq_save();
    uint16_t val = *(volatile uint16_t *)ptr;
    if (val == *(uint16_t *)expected) {
        *(volatile uint16_t *)ptr = desired;
        bflb_irq_restore(flags);
        return true;
    }
    *(uint16_t *)expected = val;
    bflb_irq_restore(flags);
    return false;
}

// 4-byte
bool __atomic_compare_exchange_4(volatile void *ptr, void *expected, uint32_t desired, bool weak, int s, int f) {
    uint32_t flags = bflb_irq_save();
    uint32_t val = *(volatile uint32_t *)ptr;
    if (val == *(uint32_t *)expected) {
        *(volatile uint32_t *)ptr = desired;
        bflb_irq_restore(flags);
        return true;
    }
    *(uint32_t *)expected = val;
    bflb_irq_restore(flags);
    return false;
}

uint8_t __atomic_load_1(const volatile void *ptr, int memorder) {
    uint32_t flags = bflb_irq_save();
    uint8_t val = *(const volatile uint8_t *)ptr;
    bflb_irq_restore(flags);
    return val;
}

uint16_t __atomic_load_2(const volatile void *ptr, int memorder) {
    uint32_t flags = bflb_irq_save();
    uint16_t val = *(const volatile uint16_t *)ptr;
    bflb_irq_restore(flags);
    return val;
}

uint32_t __atomic_load_4(const volatile void *ptr, int memorder) {
    uint32_t flags = bflb_irq_save();
    uint32_t val = *(const volatile uint32_t *)ptr;
    bflb_irq_restore(flags);
    return val;
}

void __atomic_store_1(volatile void *ptr, uint8_t val, int memorder) {
    uint32_t flags = bflb_irq_save();
    *(volatile uint8_t *)ptr = val;
    bflb_irq_restore(flags);
}

void __atomic_store_2(volatile void *ptr, uint16_t val, int memorder) {
    uint32_t flags = bflb_irq_save();
    *(volatile uint16_t *)ptr = val;
    bflb_irq_restore(flags);
}

void __atomic_store_4(volatile void *ptr, uint32_t val, int memorder) {
    uint32_t flags = bflb_irq_save();
    *(volatile uint32_t *)ptr = val;
    bflb_irq_restore(flags);
}

uint8_t __atomic_exchange_1(volatile void *ptr, uint8_t val, int memorder) {
    uint32_t flags = bflb_irq_save();
    uint8_t old = *(volatile uint8_t *)ptr;
    *(volatile uint8_t *)ptr = val;
    bflb_irq_restore(flags);
    return old;
}

uint16_t __atomic_exchange_2(volatile void *ptr, uint16_t val, int memorder) {
    uint32_t flags = bflb_irq_save();
    uint16_t old = *(volatile uint16_t *)ptr;
    *(volatile uint16_t *)ptr = val;
    bflb_irq_restore(flags);
    return old;
}

uint32_t __atomic_exchange_4(volatile void *ptr, uint32_t val, int memorder) {
    uint32_t flags = bflb_irq_save();
    uint32_t old = *(volatile uint32_t *)ptr;
    *(volatile uint32_t *)ptr = val;
    bflb_irq_restore(flags);
    return old;
}
