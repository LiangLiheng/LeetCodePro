{
    "reasoning": "Step 1: Build output structure from scratch - Construct a JSON object containing 'reasoning' and 'result' fields with no pre-existing template.

Step 2: Populate 'reasoning' field with THIS task's analysis - (a) State the exact inputs, outputs, and constraints from THIS problem statement. (b) Decompose THIS problem into specific executable sub-tasks using concrete operations (e.g., 'iterate through linked list nodes', 'count group size', 'check if size is even', 'reverse current segment'—not generic 'process data'). (c) For each sub-task, identify the specific algorithm, data structure, or logic pattern needed.

Step 3: Populate 'result' field with actual implementation - Write the complete solution code in the specified language. Use the provided template structure and fill in ALL logic. Every sub-task from Step 2b must have corresponding executable code. Zero placeholders: no '[implementation]', no '...', no 'TODO', no bracket descriptions, no template text.

Step 4: Verify by reading your code aloud - Extract the first 5 lines from your 'result' field content and state them verbatim. Do they begin with language keywords like 'class Solution', 'def functionName', 'ListNode* temp', 'for (int i'? Do they contain actual operations like assignments, function calls, conditionals? If ANY line contains English descriptions or placeholder markers instead of executable syntax, your 'result' field failed—delete it completely and rewrite from Step 3 with actual code.

Step 5: Confirm JSON structure completeness - Verify matching braces, proper quotes, correct field names ('reasoning' and 'result'), comma separation, and that both fields contain actual substantive content.",
    "result": "Write complete executable implementation in the specified language using the template structure provided. Code must be syntactically valid and immediately runnable for THIS specific task with no modifications, placeholders, or gaps."
}