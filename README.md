# jos_faust
C++ Modules for use with the JUCE Framework, generated from jos functions in the Faust Libraries

Add this jos_faust folder as a new module in Projucer, or
drag it into your JUCE modules directory.

#Why?

Since Faust compiles to C++, there is no real need for this module.  However, it offers the following benefits:

    * No Faust installation required.  The C++ here is tracked source ( but see ./faust-src/README.md ).
    * When working with JUCE, a ready-to-use JUCE-format C++ module is convenient to have.
    * Doxygen documentation (like JUCE's) is generated.
    * More "curation" of selected functions, while the Faust Libraries Distribution is more open, as it should be.<br/>
      (The algorithm is simply to add functions as they get used in real projects.)

#Status

Just getting started. Two reverberators so far (used in JackTrip), plus the Doxygen mechanics.
