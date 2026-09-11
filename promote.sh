#!/bin/bash
set -e

TIMESTAMP=$(date +%Y%m%d_%H%M%S)

git checkout stg
git merge dev --no-edit
git tag "release_$TIMESTAMP"
git push origin stg --tags
git checkout dev

