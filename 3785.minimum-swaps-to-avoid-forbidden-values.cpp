Step 1: Problem Analysis - State Specifics
Your opening must contain: the specific input types with their actual constraints from this problem (e.g., 'array of integers with length 1-10^5'), the exact output type and requirements (e.g., 'single integer representing minimum count'), the precise operations allowed (quote directly from problem), and the most critical constraint with its actual value. Use actual terminology from THIS problem statement, not generic placeholders. If your paragraph could apply to multiple different problems, it lacks required specificity.

Step 2: Algorithm Selection - Demonstrate Choice Process
Describe in past tense how you selected your approach: 'I considered [approach A] which would [specific behavior], but rejected it because [specific shortcoming with this problem]. I selected [approach B] because [specific advantage for this problem's constraints]. My algorithm: [concrete sequence of operations with actual data structures named].' State time complexity as O(expression) and space complexity as O(expression) with justification referencing specific operations. If you cannot justify complexity claims with actual operations from your algorithm, the algorithm is insufficiently detailed.

Step 3: Example Validation - Show Complete Traces
For every provided example, produce a complete trace using this exact format:
'Example [number]: Input nums=[actual values], forbidden=[actual values]. Initial state: [describe configuration]. Operation 1: swap indices [i] and [j], nums becomes [new values], satisfies [which positions]. Operation 2: [specific action], nums becomes [values], satisfies [positions]. Final: [output value]. Expected: [value from problem]. Match: YES/NO.'
If ANY example shows NO, stop immediately, revise your algorithm in Step 2, and redo all traces. Do not proceed to Step 4 until achieving YES on all examples.

Step 4: Impossibility Analysis - Prove Conditions
If the problem allows impossible cases, derive the mathematical or logical condition: 'Impossible when [specific property stated formally]. Proof: [logical argument]. Example: given nums=[values], forbidden=[values], at position [X] we need value ≠ [forbidden[X]], but [concrete reason why impossible based on available values]. Detection: [specific check implementable in code].' Show an actual impossible case with specific values, not abstract description.

Step 5: Edge Cases - Verify Behaviors
For each category, show actual behavior: 'Already valid input: nums=[values], forbidden=[values]. My algorithm produces [specific execution trace]. Output: [value]. Correct because [justification].' Cover: already valid, impossible case, minimum size (n=1 or smallest), maximum size approximation, duplicate values. Each category needs specific input values and demonstrated execution.

Step 6: Implementation - Zero Placeholders
Before writing code, state: 'My implementation has [number] functions/methods named [list names], [number] main logic blocks handling [list purposes], returns [exact type and meaning]. I verified it contains zero placeholder comments.' Then write complete code. After writing, count placeholder comments (e.g., '// TODO', '// implement', '...'). If count > 0, delete code and rewrite until count = 0.

Step 7: Pre-Submission Verification - Document Findings
For each item, state your specific finding:
'Placeholder count: I examined my code and found [number] placeholders [list them or state "none found"].
Example verification: I traced Example 1 and got [result], Example 2 got [result], all match [YES/NO].
Return type: My code returns [actual type] which matches required [type] [YES/NO].
Impossibility handling: My code detects impossibility by [specific check] and returns [value] which matches requirement [YES/NO].
Edge case coverage: I verified [list each edge case category] all produce correct outputs [YES/NO].
Compilation: I mentally traced execution with [example] and found [no errors / these errors: ...].
Algorithm match: Code implements [operations] matching Step 2 algorithm [YES/NO].'
If any NO or unverified item exists, you must stop and fix that specific item before submitting solution.

Format requirements:
- All reasoning must use past tense demonstrating completed work ('I analyzed...', 'I calculated...'), never imperative ('Analyze...', 'Calculate...') or instructional language
- Every paragraph must reference at least one specific element using its actual name/value from the problem (not 'the input' but 'the nums array' or 'index i and j')
- Your reasoning must not contain the words 'must', 'should', 'requirement', or any phrase describing what you/others should do - these indicate instructions rather than executed work
- If your reasoning could be reused as a template for other problems without modification, it lacks required problem-specific content