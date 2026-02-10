WARNING: This guide has TWO distinct parts that serve different purposes. DO NOT confuse them.

PART 1: INTERNAL REASONING PROCESS (Execute these steps - DO NOT copy them into your output)

This is your thinking process. Work through each step internally with YOUR specific problem details.

Step 1 - Problem Analysis:
YOU MUST complete for YOUR current problem:
- What EXACTLY does this problem ask you to produce? (State the precise output requirement)
- What are ALL the constraints? (List each one that affects your solution)
- Trace through EVERY provided example to understand the pattern

Step 2 - Initial Approach:
YOU MUST propose a concrete strategy for YOUR problem:
- State the EXACT algorithm/approach you will use
- Explain WHY this approach fits your problem's constraints
- Estimate time and space complexity

Step 3 - MANDATORY EXAMPLE VERIFICATION:
FOR EACH example in YOUR problem:
- Trace your approach step-by-step with the example's concrete values
- Write down what your approach produces
- Compare with the expected output
- IF ANY MISMATCH: STOP IMMEDIATELY. Your approach is wrong. Revise and re-verify ALL examples.
- ONLY proceed when ALL examples PASS

Step 4 - Component Testing (for complex logic):
IF your approach has non-trivial logic or helper functions:
- Isolate EACH component
- Test it independently with a small concrete case
- Verify output matches expectation
- Do this BEFORE integrating components together

Step 5 - Assumption Validation:
- List EVERY assumption your solution makes
- Verify each assumption is valid for YOUR problem's constraints
- If ANY assumption is questionable: reconsider your approach

Step 6 - Implementation:
Write the ACTUAL, COMPLETE code that solves YOUR problem.
- No placeholder text
- No generic descriptions
- Must be executable in the required language
- Must match any provided template format

Step 7 - Code Trace Verification:
Pick at least ONE example from YOUR problem:
- Execute your code line-by-line with the example's values
- Track what happens at each step
- Verify the final output matches the expected result
- If MISMATCH: debug and fix before proceeding

Step 8 - Edge Case Check:
Verify your solution handles:
- Minimum and maximum input sizes from constraints
- Boundary values
- Special cases mentioned in the problem

CRITICAL VERIFICATION CHECKPOINT - Answer these before outputting:
1. Does your reasoning contain YOUR problem's actual details (not generic placeholders)?
2. Does your code solve YOUR specific problem (not a different problem)?
3. Have you traced through YOUR examples and verified outputs match?
4. Is your code complete and executable (no placeholder text)?

If you answered NO to ANY question: You have NOT completed the task. Go back and complete the steps properly.

---

PART 2: OUTPUT FORMAT SPECIFICATION (How to format your final answer)

After completing the internal reasoning process above, format your solution as a JSON object:

{
    "reasoning": "Your step-by-step reasoning for YOUR specific problem. This should contain your actual work from steps 1-8 above, applied to YOUR problem with YOUR problem's details.",
    "result": "Your complete, working code that solves YOUR problem. This must be actual executable code in the required language, properly formatted according to any template provided."
}

CRITICAL: The JSON fields should contain YOUR ACTUAL WORK, not the process guide itself.
- "reasoning" = your problem-specific analysis and decisions (what you figured out)
- "result" = your working code implementation (what you wrote)

DO NOT copy the process steps into the JSON output.
DO NOT include placeholder text like "YOUR ACTUAL CODE HERE" in the result field.
DO use the process steps as your internal thinking guide, then output your actual work.