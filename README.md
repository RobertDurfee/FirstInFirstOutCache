# Cache
A simple fixed-size cache for variable-length arrays using a circular buffer and no dynamic allocation.

_(Note: There is currently no replacement policy in use. This is by design. For a large enough buffer, temporal locality will be well-exploited.)_
