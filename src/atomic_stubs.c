#include <stdint.h>
#include <stdbool.h>
#include <bflb_irq.h>

/*
 * atomic_stubs.c
 *
 * Purpose:
 *   Provide basic GCC __atomic_* runtime functions for projects
 *   using BouffaloSDK and a RISC-V target.
 *
 * Supported operations:
 *   - Compare and exchange
 *   - Atomic load
 *   - Atomic store
 *   - Atomic exchange
 *
 * Supported data sizes:
 *   - 1 byte  (8 bits)
 *   - 2 bytes (16 bits)
 *   - 4 bytes (32 bits)
 *
 * Implementation:
 *   Interrupts are disabled during each operation to prevent
 *   ordinary interrupt handlers from interrupting the critical
 *   read/write sequence.
 *
 *   bflb_irq_save() saves the previous interrupt state.
 *   bflb_irq_restore() restores that saved state.
 *
 * Limitations:
 *   - Memory-order parameters are currently ignored.
 *   - The weak compare-exchange parameter is currently ignored.
 *   - Only the operations and data sizes listed above are provided.
 *   - Disabling interrupts alone does not guarantee atomicity
 *     between multiple CPU cores or other independent bus masters.
 *
 * These functions provide basic runtime compatibility. They do not
 * implement the complete GCC atomic-operation specification.
 */


/* ============================================================
 * Atomic compare-and-exchange
 * ============================================================
 *
 * Compare the value at ptr with the value pointed to by expected.
 *
 * If the values are equal:
 *   - Write desired to ptr.
 *   - Return true.
 *   - Leave expected unchanged.
 *
 * If the values are different:
 *   - Leave ptr unchanged.
 *   - Update *expected with the actual value read from ptr.
 *   - Return false.
 *
 * Parameters:
 *   ptr     - Address of the value to compare and potentially update.
 *   expected- Address containing the expected current value.
 *             On failure, this location receives the actual value.
 *   desired - New value to write if the comparison succeeds.
 *   weak    - Weak compare-exchange flag; unused in this implementation.
 *   s       - Memory-order parameter for success; currently unused.
 *   f       - Memory-order parameter for failure; currently unused.
 *
 * Return:
 *   true  if the comparison succeeds and the value is updated.
 *   false if the comparison fails.
 *
 * The suffix _1, _2, or _4 indicates the data size in bytes.
 */


/* Compare and exchange a 1-byte value. */
bool __atomic_compare_exchange_1(
    volatile void *ptr,
    void *expected,
    uint8_t desired,
    bool weak,
    int s,
    int f)
{
    // Save the current interrupt state and disable interrupts.
    // The returned flags must be passed to irq_restore() so that
    // the previous interrupt state can be restored correctly.
    uint32_t flags = bflb_irq_save();

    // Read the current 8-bit value from the target address.
    uint8_t val = *(volatile uint8_t *)ptr;

    // Check whether the actual value matches the expected value.
    if (val == *(uint8_t *)expected) {

        // The comparison succeeded. Store the desired value.
        *(volatile uint8_t *)ptr = desired;

        // Restore the interrupt state that existed before this call.
        bflb_irq_restore(flags);

        // Report that the comparison and update succeeded.
        return true;
    }

    // The comparison failed. Report the actual value to the caller
    // through expected, allowing the caller to inspect or retry.
    *(uint8_t *)expected = val;

    // Restore the previous interrupt state.
    bflb_irq_restore(flags);

    // Report that the comparison failed.
    return false;
}


/* Compare and exchange a 2-byte value. */
bool __atomic_compare_exchange_2(
    volatile void *ptr,
    void *expected,
    uint16_t desired,
    bool weak,
    int s,
    int f)
{
    // Save the current interrupt state and disable interrupts.
    uint32_t flags = bflb_irq_save();

    // Read the current 16-bit value from the target address.
    uint16_t val = *(volatile uint16_t *)ptr;

    // Check whether the actual value matches the expected value.
    if (val == *(uint16_t *)expected) {

        // The comparison succeeded. Store the desired value.
        *(volatile uint16_t *)ptr = desired;

        // Restore the previous interrupt state.
        bflb_irq_restore(flags);

        return true;
    }

    // The comparison failed. Update expected with the actual value.
    *(uint16_t *)expected = val;

    // Restore the previous interrupt state.
    bflb_irq_restore(flags);

    return false;
}


/* Compare and exchange a 4-byte value. */
bool __atomic_compare_exchange_4(
    volatile void *ptr,
    void *expected,
    uint32_t desired,
    bool weak,
    int s,
    int f)
{
    // Save the current interrupt state and disable interrupts.
    uint32_t flags = bflb_irq_save();

    // Read the current 32-bit value from the target address.
    uint32_t val = *(volatile uint32_t *)ptr;

    // Check whether the actual value matches the expected value.
    if (val == *(uint32_t *)expected) {

        // The comparison succeeded. Store the desired value.
        *(volatile uint32_t *)ptr = desired;

        // Restore the previous interrupt state.
        bflb_irq_restore(flags);

        return true;
    }

    // The comparison failed. Update expected with the actual value.
    *(uint32_t *)expected = val;

    // Restore the previous interrupt state.
    bflb_irq_restore(flags);

    return false;
}


/* ============================================================
 * Atomic load
 * ============================================================
 *
 * Read a value from the specified memory address.
 *
 * The interrupt state is saved before the read and restored
 * immediately afterward.
 *
 * Parameters:
 *   ptr      - Address from which to read.
 *   memorder - Requested memory ordering; unused in this version.
 *
 * Return:
 *   The value read from memory.
 */


/* Load a 1-byte value. */
uint8_t __atomic_load_1(const volatile void *ptr, int memorder)
{
    // Save the interrupt state and disable interrupts.
    uint32_t flags = bflb_irq_save();

    // Read the 8-bit value from memory.
    uint8_t val = *(const volatile uint8_t *)ptr;

    // Restore the previous interrupt state.
    bflb_irq_restore(flags);

    // Return the value read.
    return val;
}


/* Load a 2-byte value. */
uint16_t __atomic_load_2(const volatile void *ptr, int memorder)
{
    // Save the interrupt state and disable interrupts.
    uint32_t flags = bflb_irq_save();

    // Read the 16-bit value from memory.
    uint16_t val = *(const volatile uint16_t *)ptr;

    // Restore the previous interrupt state.
    bflb_irq_restore(flags);

    // Return the value read.
    return val;
}


/* Load a 4-byte value. */
uint32_t __atomic_load_4(const volatile void *ptr, int memorder)
{
    // Save the interrupt state and disable interrupts.
    uint32_t flags = bflb_irq_save();

    // Read the 32-bit value from memory.
    uint32_t val = *(const volatile uint32_t *)ptr;

    // Restore the previous interrupt state.
    bflb_irq_restore(flags);

    // Return the value read.
    return val;
}


/* ============================================================
 * Atomic store
 * ============================================================
 *
 * Write a value to the specified memory address.
 *
 * Parameters:
 *   ptr      - Destination address.
 *   val      - Value to write.
 *   memorder - Requested memory ordering; unused in this version.
 *
 * Return:
 *   None.
 */


/* Store a 1-byte value. */
void __atomic_store_1(volatile void *ptr, uint8_t val, int memorder)
{
    // Save the interrupt state and disable interrupts.
    uint32_t flags = bflb_irq_save();

    // Write the 8-bit value to memory.
    *(volatile uint8_t *)ptr = val;

    // Restore the previous interrupt state.
    bflb_irq_restore(flags);
}


/* Store a 2-byte value. */
void __atomic_store_2(volatile void *ptr, uint16_t val, int memorder)
{
    // Save the interrupt state and disable interrupts.
    uint32_t flags = bflb_irq_save();

    // Write the 16-bit value to memory.
    *(volatile uint16_t *)ptr = val;

    // Restore the previous interrupt state.
    bflb_irq_restore(flags);
}


/* Store a 4-byte value. */
void __atomic_store_4(volatile void *ptr, uint32_t val, int memorder)
{
    // Save the interrupt state and disable interrupts.
    uint32_t flags = bflb_irq_save();

    // Write the 32-bit value to memory.
    *(volatile uint32_t *)ptr = val;

    // Restore the previous interrupt state.
    bflb_irq_restore(flags);
}


/* ============================================================
 * Atomic exchange
 * ============================================================
 *
 * Replace the value at ptr with a new value and return the old one.
 *
 * The read and write are performed while interrupts are disabled.
 *
 * Parameters:
 *   ptr      - Address of the value to exchange.
 *   val      - New value to write.
 *   memorder - Requested memory ordering; unused in this version.
 *
 * Return:
 *   The value that was stored at ptr before the exchange.
 */


/* Exchange a 1-byte value. */
uint8_t __atomic_exchange_1(
    volatile void *ptr,
    uint8_t val,
    int memorder)
{
    // Save the interrupt state and disable interrupts.
    uint32_t flags = bflb_irq_save();

    // Read and preserve the original 8-bit value.
    uint8_t old = *(volatile uint8_t *)ptr;

    // Replace the original value with the new value.
    *(volatile uint8_t *)ptr = val;

    // Restore the previous interrupt state.
    bflb_irq_restore(flags);

    // Return the original value.
    return old;
}


/* Exchange a 2-byte value. */
uint16_t __atomic_exchange_2(
    volatile void *ptr,
    uint16_t val,
    int memorder)
{
    // Save the interrupt state and disable interrupts.
    uint32_t flags = bflb_irq_save();

    // Read and preserve the original 16-bit value.
    uint16_t old = *(volatile uint16_t *)ptr;

    // Replace the original value with the new value.
    *(volatile uint16_t *)ptr = val;

    // Restore the previous interrupt state.
    bflb_irq_restore(flags);

    // Return the original value.
    return old;
}


/* Exchange a 4-byte value. */
uint32_t __atomic_exchange_4(
    volatile void *ptr,
    uint32_t val,
    int memorder)
{
    // Save the interrupt state and disable interrupts.
    uint32_t flags = bflb_irq_save();

    // Read and preserve the original 32-bit value.
    uint32_t old = *(volatile uint32_t *)ptr;

    // Replace the original value with the new value.
    *(volatile uint32_t *)ptr = val;

    // Restore the previous interrupt state.
    bflb_irq_restore(flags);

    // Return the original value.
    return old;
}
