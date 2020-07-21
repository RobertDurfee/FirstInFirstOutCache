# Circular Cache
A simple, fixed-size cache for contiguous, variable-length arrays using a circular buffer and static allocation.

_(Note: There is currently no replacement policy in use. This is by design. For a large enough buffer, temporal locality is well-exploited.)_
