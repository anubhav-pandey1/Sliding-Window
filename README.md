# Sliding Window Technique
- Optimizing operations on continuous sub-elements using the sliding window technique.
- We will convert brute force algorithms to optimized algorithms with better asymptotic time complexity.
- Usually useful for performing optimized operations on continuous sub-elements of an ADT.

### Steps:
1. Identify a brute force approach to fulfill the requirement.
2. Identify the repetitive aspect of this approach in performing operations on the continuous sub-elements.
3. Improve this repetitive aspect to optimize, using a continuous window of sub-elements.

### Identification:
1. Continuous ADTs like arrays and strings (continuous, not contiguous).
2. Continuous sub-elements like subarrays or substrings to form the window or the window size.
3. Operations on the sub-elements (window) to derive a result.

### Types:
1. Fixed-size window: Perform operations along with window movement
2. Variable-size window: Calculate window-size given certain conditions
