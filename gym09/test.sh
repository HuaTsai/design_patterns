#!/bin/bash

for file in testdata/*.in; do
  stem="$(basename "${file}" .in)"
  bin/main < ${file} > /tmp/${stem}.out
  diff -q /tmp/${stem}.out ${file%.in}.out
done

