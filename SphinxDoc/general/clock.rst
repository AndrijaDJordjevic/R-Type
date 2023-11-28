.. _clock:

Clock
=====

|

Introduction
------------

The clock allows to execute code at regular intervals. More concretly for sprites animation or draw loop.

|

The Clock class
---------------

.. code-block:: c++

    class Clock {
        public:
            Clock(float refreshRate);
            ~Clock() = default;
            bool refresh();
            bool canUpdate(float delay, float &lastUpdate) const;
            float getTimeMilli() const;
        private:
            std::chrono::steady_clock _clock;
            std::chrono::steady_clock::time_point _lastRefresh;
            float _refreshRate;
    };

refresh method
^^^^^^^^^^^^^^

It check if the main refresh rate is reached. If it is, it update the last refresh time and return true. Otherwise it return false.

canUpdate method
^^^^^^^^^^^^^^^^

It check if the given delay is reached. If it is, it update the last update time given and return true. Otherwise it return false.

getTimeMilli method
^^^^^^^^^^^^^^^^^^^

Simply return the elapsed time in milliseconds.
