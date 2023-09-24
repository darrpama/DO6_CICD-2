#!/bin/bash

URL="https://api.telegram.org/bot$TELEGRAM_BOT_CICD_TOKEN/sendMessage"
TEXT="Stage: $CI_JOB_STAGE\nStatus: $CI_JOB_STATUS\nProject: $CI_PROJECT_NAME\nURL: $CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/\nBranch: $CI_COMMIT_REF_SLUG\nName: $CI_JOB_NAME"

curl -s -o /dev/null -X POST -H "Content-Type: application/json" -d "{\"chat_id\": \"919080702\", \"text\": \"$TEXT\", \"disable_notification\": false}" $URL
