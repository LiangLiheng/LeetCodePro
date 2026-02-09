**WHAT YOU MUST PRODUCE FOR THIS TASK:**
For coding tasks: Actual compilable code in the 'result' field, your problem-solving thought process in the 'reasoning' field.
For math tasks: Numerical calculations/formulas in the 'result' field, your analytical steps in the 'reasoning' field.
NEVER output: This framework itself, numbered methodology steps, generic problem-solving guidance.

**INTERNAL THINKING GUIDE (DO NOT OUTPUT THIS):**

→ First instinct check: Read ALL examples carefully. What makes each example different? What patterns do I see?

→ Case identification: Do some examples represent fundamentally different scenarios? List distinct cases that might need different handling.

→ Assumption reality-test: Before committing to any approach, ask - what am I assuming? Do these assumptions hold for EVERY example including edge cases? Trace through mentally.

→ Validation against everything: For each example, mentally execute my planned approach. What output does it produce? Is it correct? If any example fails, why specifically?

→ Gap analysis: What's missing? What case isn't handled? Be concrete about failure modes.

→ Implementation bridge: For each edge case I identified, which specific part of my code handles it? If I can't point to code that addresses a critical case, my solution is incomplete.

→ Concrete execution trace: Walk through my actual implementation code with each example step-by-step. Does it produce the expected output? If not, what needs fixing?

**ANTI-PATTERN EXAMPLES (WHAT NOT TO OUTPUT):**

❌ WRONG - Copying this framework:
```json
{
  "reasoning": "Step 1: Understand the problem completely...",
  "result": "Step 2: Identify different problem cases..."
}
```

❌ WRONG - Generic methodology instead of actual work:
```json
{
  "reasoning": "I will analyze edge cases and validate my approach",
  "result": "The solution should handle all examples correctly"
}
```

✓ CORRECT - Actual work on the specific problem:
```json
{
  "reasoning": "For the supersequence problem, I notice Example 1 has overlapping chars 'a' and 'b', while Example 3 has disjoint words. I need to find minimum length strings containing each word as subsequence...",
  "result": "class Solution {\npublic:\n    vector<vector<int>> supersequences(vector<string>& words) {\n        // actual implementation code\n    }\n};"
}
```

**FINAL GATE BEFORE SUBMITTING:**
Read what you're about to submit. Ask yourself:
- Does 'result' field contain actual code/calculations/answer for THIS specific problem?
- Does 'reasoning' field contain YOUR thinking process about THIS task (not generic steps)?
- Does either field contain ANY text from this framework, ANY numbered steps, ANY meta-commentary about methodology?

If you see framework text, numbered steps, or generic methodology in your output → You failed. Delete everything. Start over with actual work on the problem.

If you see actual code, actual calculations, or actual problem-specific analysis → You succeeded. That's what belongs in the output.