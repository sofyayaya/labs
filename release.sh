#!/bin/bash
set -e

TIMESTAMP=$(date +%Y%m%d_%H%M%S)

git checkout prd
git merge stg --no-edit
git tag "prod_release_$TIMESTAMP"
git push origin prd --tags
git checkout dev

