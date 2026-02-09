{
    "reasoning": "Step 1: Problem analysis - Identify the core problem type, all requirements, constraints, and expected output format. List them explicitly: [state requirements], [state constraints], [state output format]. This ensures complete coverage during solution design.

Step 2: Constraint interaction analysis - Examine how different constraints interact with each other. For multi-constraint problems, check if satisfying one constraint might conflict with another (e.g., optimization vs. connectivity, minimization vs. threshold limits). Document potential conflicts: if constraint A requires X and constraint B requires Y, can both be satisfied simultaneously? Use counterexample testing: try to construct cases where optimizing one criterion breaks another.

Step 3: Approach generation and evaluation - List 2-3 candidate approaches with specific algorithmic strategies (not generic statements). For each approach: (a) Describe the core algorithm (binary search, graph algorithm, dynamic programming, etc.), (b) Analyze how it handles each constraint from Step 1, (c) Identify potential weaknesses or edge cases, (d) Estimate time/space complexity. Select the approach that correctly satisfies all constraints, documenting why alternatives were rejected to avoid revisiting failed strategies.

Step 4: Algorithm design with validation - For the selected approach, break down the algorithm into concrete components: (a) If using binary search: define search space bounds, feasibility check logic, convergence criteria, (b) If using graph algorithms: specify which algorithm (BFS/DFS/Dijkstra/etc.), what it validates, termination conditions, (c) If using greedy/optimization: justify why greedy choice preserves all constraints, provide counterexample test. The algorithm description should be detailed enough to implement directly.

Step 5: Implementation specification - Based on the algorithm from Step 4, specify the complete implementation:
   • Data structures needed: list each structure (arrays, hashmaps, graphs, priority queues) with initialization values
   • Helper functions: for each function, specify name, inputs, outputs, and core logic in 2-3 sentences
   • Main algorithm flow: write detailed pseudocode showing the control flow, loop structures, and key operations
   • Edge case handling: list specific edge cases (empty input, boundary values, impossible scenarios) and how each is handled
   • Output format: confirm the output structure matches the required format (e.g., JSON with specific fields, code string, nested structure)

Step 6: Code generation - Translate the implementation specification from Step 5 into complete, syntactically valid code in the required language:
   • Implement each data structure with proper initialization
   • Implement each helper function with complete logic (no placeholders like [TODO] or [IMPLEMENTATION_HERE])
   • Implement the main algorithm following the pseudocode structure
   • Add edge case handling at appropriate points
   • CRITICAL: The code must be complete and executable. Never generate placeholder text. Every function must have actual implementation logic, not generic comments or markers.

Step 7: Example validation - Take a concrete example from the problem statement. Trace through the generated code step-by-step, tracking variable values and logic flow at each step. Verify the output matches the expected result. If the traced output doesn't match expected: (a) Identify the step where execution diverges, (b) Determine if it's a logic error, edge case miss, or algorithm flaw, (c) Return to Step 6 and fix the specific issue in the code.

Step 8: Edge case verification - Test the implementation mentally on edge cases identified in Step 5: empty inputs, minimum/maximum boundary values, impossible scenarios. Confirm the code handles each appropriately (returns correct value, handles error, maintains constraints). If any edge case fails, add the necessary handling logic to the code.

Step 9: Output completeness check - Verify the result field contains: (a) Complete code with all components from Step 5, (b) Proper syntax for the specified language (class/function definitions, complete logic, return statements), (c) No placeholder text or incomplete sections, (d) Code that matches the reasoning's described approach. If this check reveals missing components, the code is incomplete and must be regenerated following Steps 5-6.

Step 10: Final output generation - Place the complete, validated implementation in the result field. The code must be directly executable in the specified language without modification. Never use placeholder text like [TODO], [IMPLEMENTATION], [PLACEHOLDER], or generic comments. Every function and logic block must be fully implemented based on the algorithm designed in Steps 4-5.",
    "result": "[COMPLETE_CODE_IMPLEMENTATION_BASED_ON_ALGORITHM_FROM_STEP_4_AND_SPECIFICATION_FROM_STEP_5]"
}