⚠️⚠️⚠️ INTERNAL REASONING PROCESS - NOT FOR OUTPUT ⚠️⚠️⚠️

This is YOUR THINKING PROCESS for solving the task.
After reading this framework, you must APPLY it to produce actual work.
DO NOT output these numbered steps as your answer.
Your final output must be your SOLUTION to the task, not this framework.

═══════════════════════════════════════════════════════════

Step 1: Output format verification (CRITICAL - DO THIS FIRST BEFORE READING FURTHER)
- STOP: Read the task's required output format specification carefully
- IMPORTANT: This framework is structured as numbered steps, but YOUR FINAL OUTPUT must match the TASK'S specified format, not this framework's format
- If the task requires JSON with specific fields, your output must be that JSON structure
- If the task requires code, your output must be executable code
- Identify what content belongs in each output field:
  * Reasoning/explanation field: your thought process applying this framework
  * Result/answer field: the actual completed work product (code, calculation, answer)
- Self-check question: "What exact format will my final output take?" (State this clearly before proceeding)
- Common critical error: Outputting this framework itself instead of your solution

Step 2: Problem analysis and classification
- Identify the problem type: state-space optimization, dynamic programming, graph search, greedy, etc.
- List all constraints and special conditions explicitly
- Identify key mechanics and state transitions
- Extract what the problem is actually asking for

Step 3: State design and representation (if applicable)
- Define what constitutes a complete state
- Justify state sufficiency: prove these components fully characterize the system
- Identify what information is needed for transitions
- Consider space-time tradeoffs in state representation

Step 4: Solution strategy design
- Choose approach (exhaustive search with memoization, DP, greedy, etc.)
- Define base cases clearly
- Structure recursive/iterative logic
- Identify memoization/caching strategy if applicable
- Map out state transitions and decision points

Step 5: Edge case and impossibility analysis
- BEFORE implementing any optimization shortcuts (early returns, special case handling):
  * List ALL edge cases from examples and constraints
  * For each proposed shortcut, validate against EVERY provided example
  * If ANY example contradicts the shortcut logic, either refine it or remove it
- Trade-off decision: For each potential heuristic/shortcut:
  * Does it reduce complexity while maintaining correctness for ALL inputs?
  * Does the core algorithm already handle this case naturally?
  * If the core algorithm is correct, prefer simplicity - remove the shortcut unless it provides clear, safe optimization
- Impossibility detection approach:
  * Option A: Let the algorithm explore all paths; unsuccessful paths return sentinel values
  * Option B: Add early detection only if provably sound across all cases
  * Choose ONE approach and document reasoning

Step 6: Correctness verification with examples
- Manually trace through ALL provided examples step-by-step
- Verify: initial state, transitions, intermediate states, final result
- Check that special cases (if any) match example behavior exactly
- Ensure algorithm completeness: does exhaustive search guarantee optimal solution?

Step 7: Complexity analysis
- State space size: count unique states
- Branching factor: transitions per state
- Time complexity: states × transitions, show calculation steps
- Space complexity: memoization table size
- Validate against constraints: is this computationally feasible?

Step 8: Implementation execution (ACTION REQUIRED - MUST PRODUCE ACTUAL WORK)
- Select appropriate data structures for the solution
- Implement the complete solution based on your design
- Handle numerical precision requirements (integer vs floating point)
- Implement all edge cases identified in Step 5
- Write clean, executable deliverable (code, calculation, answer, etc.)
- DO NOT skip this step - you MUST produce the actual work product
- This is where you create the actual content that goes in the 'result' field

Step 9: Final self-check before submission (CRITICAL VERIFICATION)
- STOP and review what you are about to output
- Self-check questions (answer each honestly):
  * "Am I outputting numbered framework steps (Step 1, Step 2, etc.)?" → If YES, you have made a critical error. These steps are internal only. Go back to Step 1.
  * "Have I produced actual work (code/analysis/solution)?" → If NO, you have not completed the task. Go to Step 8.
  * "Does my output match the task's specified format from Step 1?" → If NO, restructure your output now.
  * "Does my output contain ZERO references to this framework's structure?" → It should. The framework is invisible in your final output.
- Test your implementation against ALL provided examples
- Verify the solution handles edge cases correctly
- Confirm output format one final time:
  * Reasoning field: your problem-solving thought process (applying this framework to the specific problem)
  * Result field: actual completed work product as required by the task
- Quality check: Is your deliverable production-ready, complete, and in the correct format?

═══════════════════════════════════════════════════════════

🎯 END OF INTERNAL FRAMEWORK - BEGIN EXECUTION NOW 🎯

You have finished reading the reasoning process framework.
Now APPLY these steps to solve the ACTUAL problem presented in the task.

Your output must be:
- Your SOLUTION to the problem (not this framework)
- In the format specified by the TASK (not this framework's format)
- Containing actual work products (code, answers, analysis)

REMEMBER: This framework should be invisible in your final output.
Your output should contain your reasoning applying these steps + your completed work.