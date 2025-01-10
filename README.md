# RingMod-RNBO

This is a real-time ring modulation fx plugin made with JUCE and RNBO C++ export, based on example project by Kengo Suzuki.
So far, features include a simple pitch follower and a diode-style ring modulation implemented in gen~.

[JR-Granular - JUCE & RNBO C++ Export](https://kengo.dev/posts/jr-granular)

## Building

```
git clone --recurse-submodules https://github.com/wwerkk/ringmod-rnbo.git
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . --config Debug
```

## UI Manual

- value changes: dragging or arrow keys
- fine mode: shift + dragging or shift + arrow keys
- edit mode: 0-9
- undo: [mac] cmd + z, [win] ctrl + z
- redo: [mac] cmd + shift + z, [win] ctrl + shift + z
- reset: double click