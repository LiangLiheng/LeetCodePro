=== REASONING PROCESS FRAMEWORK ===

ATTENTION: This is a PROCESS GUIDE for how to think and work. It is NOT output to copy or reproduce. Your job is to FOLLOW these steps to CREATE your own unique analysis and implementation.

→ CRITICAL: If you are about to copy any text from this framework into your output, STOP immediately. That is not your task.

=== PHASE 1: IMMEDIATE PRODUCTION START ===

→ Step 1A: Quick Problem Scan
Read the problem statement once. Identify:
- What is the core task?
- What are the key constraints?
- What operation semantics matter? (keywords: 'independently', 'for each', 'empty and call')

→ Step 1B: START PRODUCING NOW (CANNOT SKIP)
Before reading further, RIGHT NOW:
- Write the first 3-5 lines of actual implementation code
- Even if incomplete or potentially wrong, produce concrete syntax immediately
- This is not planning - write actual code in the target language

→ CHECKPOINT: Look at what you just wrote. Is it actual code with real syntax, or descriptions/pseudocode? If descriptions, replace with real code NOW before proceeding.

=== PHASE 2: BUILD INCREMENTALLY WITH EMBEDDED VERIFICATION ===

→ Step 2A: First Major Component - Build It
Identify the primary functionality needed. Write the actual implementation code for it now.
- Not pseudocode
- Not 'TODO: implement X'
- Actual working code for this component

→ CHECKPOINT: Count lines of real implementation you just added. If zero, you're still planning. Write actual code before continuing.

→ Step 2B: Validate First Component Immediately
Take Example 1 from the problem:
- Manually trace through using ONLY what you've built so far
- Write down the output at each step
- Does it match expected behavior for this component?
- If no, fix NOW before building more

→ Step 2C: Second Major Component - Build and Integrate
Identify the next piece of functionality. Write actual implementation code and integrate with first component.

→ CHECKPOINT: Does this new code contain any placeholders like '[implement this]' or '[add logic here]'? If yes, replace ALL placeholders with actual implementation NOW.

→ Step 2D: Remaining Components - Iterative Build
For each additional component:
1. Write actual implementation code (no placeholders)
2. Check: 'Could someone use this code without filling gaps?' If no, fill gaps immediately
3. Verify integration with existing components
4. Test with one example to catch issues early

→ Step 2E: Premature Optimization Check
Before ANY optimization:
- Does your current implementation pass all examples with correct semantics?
- Are you about to change 'independent operations' into 'reused computations'?
- If the problem says 'empty and call for each', does your optimization preserve this?
- Only proceed with optimizations that provably preserve exact semantics

=== PHASE 3: CORRECTNESS VERIFICATION (EMBEDDED IN PRODUCTION) ===

→ Step 3A: Test Against ALL Examples
For each provided example:
- Manually trace through with your complete implementation
- Write down intermediate values at each step
- Compare final output with expected result
- If ANY example fails, identify root cause and fix before proceeding

→ Step 3B: Semantic Preservation Check
When problem states operations are 'independent' or 'for each separately':
- Does your implementation truly execute them independently?
- Or are you combining/reusing results in ways that change semantics?
- Trace through: what fundamentally differs between separate executions?
- If your approach changes independence semantics, revert to correct semantics

→ Step 3C: Requirements Completeness
List every explicit requirement from problem statement:
- For each requirement, identify the specific code that addresses it
- If any requirement lacks implementation, add it NOW
- Verify no implicit assumptions that contradict stated requirements

=== PHASE 4: ONLY AFTER CORRECTNESS - SAFE OPTIMIZATION ===

→ Step 4A: Post-Correctness Optimization Only
Your implementation passes all tests. Now consider optimizations:
- For each optimization, explicitly verify it preserves semantics
- Re-test all examples after EACH optimization
- If any test fails, revert the optimization immediately

=== MANDATORY PRE-SUBMISSION VERIFICATION ===

→ DELIVERABLE COMPLETENESS CHECK:
Look at your implementation output. Does it contain:
✓ Complete, runnable code ready to use without modification?
✗ Any placeholders: [placeholder], [code here], [implement X], TODO comments?
✗ Pseudocode or descriptions instead of actual code?
✗ Incomplete sections requiring someone to fill in gaps?

If ANY ✗ items exist, go back and produce actual complete implementation NOW.

→ USABILITY TEST:
If someone took ONLY your implementation code, could they:
✓ Run it directly without any modifications?
✗ Need to replace placeholders or add missing logic?

If answer is ✗, you have NOT completed the task. Produce complete implementation now.

→ FINAL CORRECTNESS REVALIDATION:
- Re-test against ALL examples one final time
- Verify exact adherence to problem specifications
- Confirm no unintended semantic changes from optimizations

→ If verification fails: Fix issues before submission. Submitting incomplete work guarantees failure.

=== REMEMBER: YOUR OUTPUT MUST BE YOUR OWN WORK ===
Your output should be:
- Your unique analysis of THIS specific problem
- Your actual implementation code for THIS problem
- NOT a reproduction of this framework
- NOT a template with placeholders

This framework guides your THINKING PROCESS. Your OUTPUT is the actual work product you create by following this process.