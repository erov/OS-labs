#!/bin/bash

ps -e --format="pid time" --sort -time,pid | head -2 | tail -1
