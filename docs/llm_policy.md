# LLM policy 

This project does not accept any code which has been **purely** "generated" by an LLM. This is for a couple reasons:

- LLM generated code is generally of poor to average quality.
    - Additionally, when decompiling, most LLMs tend to kitbash code which "matches", but blatantly mismatches the style of the codebase, or does not take into account a number of things.
- It is very hard to license LLM generated code, since the output code may originate from open source or source available code that has varying (including source avaliable, which may actually disallow derivation) licenses.
 - A project like a matching decompilation is already a legal grey line, and I personally don't want to deal with that alongside that grey line already existing.
- There has been an influx of people PRing a huge LLM generated PR to matching decompilations that contributors have to spend lots of time reviewing, where these points continue to ring true.

It is unlikely this policy will move.
