Step 1: Analyze the problem requirements and identify key constraints that define valid solutions.

Step 2: Determine the algorithmic approach - consider whether the problem requires enumeration, dynamic programming, greedy strategy, or other algorithmic patterns.

Step 3: Break down the solution into logical components - data structures needed, helper functions, main algorithm flow.

Step 4: Design the implementation strategy - outline how components interact, what order operations occur, and how edge cases are handled.

Step 5: Consider optimization opportunities - time complexity, space complexity, and any precomputation that reduces runtime.

Step 6: Trace through examples to validate logic - walk through provided examples step-by-step to ensure the approach produces correct outputs.

Step 7: Identify edge cases - minimum/maximum input values, empty inputs, single elements, boundary conditions specific to the problem.

Step 8: Implement the solution following the template structure. Preserve all template markers (@lc code=start, @lc code=end, class/function signatures) and write complete, syntactically valid code.

Step 9: Construct output as single-level JSON with two fields: 'reasoning' (string with your problem-solving explanation) and 'result' (string with ONLY code). Check your 'result' field: Does it start with code syntax (# or class or def) or with curly brace {? If it starts with { you have nested JSON - WRONG. Extract the code portion and make it the direct string value of 'result'. Correct structure: {"reasoning": "...", "result": "# code starts here..."}. Incorrect structure: {"reasoning": "...", "result": "{\"reasoning\": ..., \"result\": ...}"}. If you see the incorrect pattern, restructure immediately.