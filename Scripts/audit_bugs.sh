#!/usr/bin/env bash
# =============================================================================
# Scripts/audit_bugs.sh
# Exhaustive mechanical bug-pattern audit for all 4 owner mods.
#
# Usage:
#   cd <repo-root>
#   bash Scripts/audit_bugs.sh
#
# Exit code: 0 = no issues found, 1 = one or more issues found.
#
# Each check is applied to EVERY source file in all 4 mods so that a pattern
# fixed in one file is automatically verified across the entire codebase.
# This prevents the class of miss where a bug is caught in the first file
# encountered but identical code in other files goes unnoticed.
# =============================================================================

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
MOD_ROOT="$REPO_ROOT/Mods"

# Directories that contain owner-authored code (excludes SML/Alpakit/etc.)
OWNER_MODS=(
    "$MOD_ROOT/BanChatCommands/Source"
    "$MOD_ROOT/BanSystem/Source"
    "$MOD_ROOT/DiscordBridge/Source"
    "$MOD_ROOT/SMLWebSocket/Source"
)

RED='\033[0;31m'
YEL='\033[0;33m'
GRN='\033[0;32m'
NC='\033[0m'

ISSUES=0

# Helper: print a finding and increment the counter.
fail() {
    local check="$1"; shift
    echo -e "${RED}[FAIL]${NC} ${YEL}${check}${NC}"
    while [[ $# -gt 0 ]]; do
        echo "       $1"; shift
    done
    echo
    ISSUES=$((ISSUES + 1))
}

pass() {
    echo -e "${GRN}[PASS]${NC} $1"
}

# Build a single grep path list from all owner mod source directories.
MOD_PATHS=()
for d in "${OWNER_MODS[@]}"; do
    if [[ -d "$d" ]]; then
        MOD_PATHS+=("$d")
    fi
done

list_cpp_files() {
    [[ ${#MOD_PATHS[@]} -gt 0 ]] || return 0
    find "${MOD_PATHS[@]}" -name "*.cpp" -print0 2>/dev/null
}

list_header_files() {
    [[ ${#MOD_PATHS[@]} -gt 0 ]] || return 0
    find "${MOD_PATHS[@]}" -name "*.h" -print0 2>/dev/null
}

list_source_files() {
    [[ ${#MOD_PATHS[@]} -gt 0 ]] || return 0
    find "${MOD_PATHS[@]}" \( -name "*.cpp" -o -name "*.h" \) -print0 2>/dev/null
}

echo "========================================================"
echo " DiscordBridge bug-pattern audit"
echo " Scanning ${#MOD_PATHS[@]} mod source tree(s)"
echo "========================================================"
echo

echo " Files queued for scan:"
found_any=0
while IFS= read -r -d '' file; do
    echo "  - $file"
    found_any=1
done < <(list_source_files | sort -z)

if [[ "$found_any" -eq 0 ]]; then
    echo "  (none)"
fi

echo

# =============================================================================
# CHECK 1: INT64_MAX guard on NextId increment
#
# Pattern: any "NextId = <expr>.Id + 1" without the guard
# "(E.Id < INT64_MAX) ? E.Id + 1 : E.Id" (or equivalent).
#
# When a file has "NextId = X.Id + 1" but NOT the INT64_MAX guard string, it
# is a potential overflow.  We look for the plain increment pattern and then
# verify the guard is present in the same file.
# =============================================================================
echo "--- CHECK 1: INT64_MAX guard on all NextId increment loops ---"

while IFS= read -r -d '' file; do
    # Does this file contain an unguarded "= X.Id + 1" NextId assignment?
    if grep -qP '\bNextId\s*=\s*\(?\w+\.Id\s*\+\s*1' "$file"; then
        # Good only if the INT64_MAX guard is present somewhere in the file.
        if ! grep -qP 'INT64_MAX' "$file"; then
            fail "CHECK 1 – INT64_MAX guard" \
                "File: $file" \
                "Has 'NextId = X.Id + 1' but no INT64_MAX guard." \
                "Fix: wrap the increment:  NextId = (X.Id < INT64_MAX) ? X.Id + 1 : X.Id;"
        fi
    fi
done < <(list_cpp_files)

pass "CHECK 1 done"
echo

# =============================================================================
# CHECK 2: Temp file cleanup on IFileManager::Move() failure
#
# Every SaveToFile() that does:
#   1. FFileHelper::SaveStringToFile(..., *TmpPath, ...)
#   2. IFileManager::Get().Move(*Dest, *TmpPath, ...)
# must also call IFileManager::Get().Delete(*TmpPath) in the failure branch.
#
# Strategy: find every file that calls both SaveStringToFile and Move.
# Then verify that Delete(*TmpPath) also appears (even if on the happy path
# the Move succeeds, the error branch must clean up).
# =============================================================================
echo "--- CHECK 2: Temp file cleanup after IFileManager::Move() failure ---"

while IFS= read -r -d '' file; do
    has_save=$(grep -cP 'SaveStringToFile' "$file")
    has_move=$(grep -cP 'IFileManager::Get\(\)\.Move' "$file")
    if [[ "$has_save" -gt 0 && "$has_move" -gt 0 ]]; then
        has_delete=$(grep -cP 'IFileManager::Get\(\)\.Delete' "$file")
        if [[ "$has_delete" -eq 0 ]]; then
            fail "CHECK 2 – temp file cleanup" \
                "File: $file" \
                "Uses SaveStringToFile + Move but has no IFileManager::Get().Delete() call." \
                "Fix: add IFileManager::Get().Delete(*TmpPath) in the Move failure branch."
        fi
    fi
done < <(list_cpp_files)

pass "CHECK 2 done"
echo

# =============================================================================
# CHECK 3: FDateTime::ParseIso8601 return value checked
#
# Every call to FDateTime::ParseIso8601() must use its bool return value.
# Bare "FDateTime::ParseIso8601(...)" (without assigning or checking the bool)
# silently leaves the output FDateTime unchanged on malformed input.
# =============================================================================
echo "--- CHECK 3: FDateTime::ParseIso8601() return value not ignored ---"

while IFS= read -r -d '' file; do
    # A call is "unchecked" when ParseIso8601 appears at the start of a
    # statement (i.e., not assigned to a variable or used in a condition).
    # Pattern: line is like "    FDateTime::ParseIso8601(..." without if/=.
    if grep -qP '^\s*FDateTime::ParseIso8601\s*\(' "$file"; then
        fail "CHECK 3 – ParseIso8601 return ignored" \
            "File: $file" \
            "FDateTime::ParseIso8601() return value is not checked (call result discarded)." \
            "Fix: use 'if (!FDateTime::ParseIso8601(..., Out)) { /* handle error */ }'"
        grep -nP '^\s*FDateTime::ParseIso8601\s*\(' "$file" | while IFS= read -r ln; do
            echo "       Line: $ln"
        done
    fi
done < <(list_cpp_files)

pass "CHECK 3 done"
echo

# =============================================================================
# CHECK 4: BIO_write / BIO_read return value checked for < 0
#
# OpenSSL BIO functions return -1 on error, not 0.  An equality check
# "Written != BytesRead" catches it numerically but the error branch should
# explicitly test for negative values first to avoid misleading log output.
# =============================================================================
echo "--- CHECK 4: BIO_write/BIO_read return values handled correctly ---"

while IFS= read -r -d '' file; do
    if grep -qP '\bBIO_write\b|\bBIO_read\b' "$file"; then
        # Warn if no "< 0" or "<0" check is present alongside BIO calls.
        if ! grep -qP '<\s*0' "$file"; then
            fail "CHECK 4 – BIO_write/BIO_read negative return" \
                "File: $file" \
                "Uses BIO_write or BIO_read but has no '< 0' error check." \
                "Fix: check 'if (Written < 0)' before '!= BytesRead' comparison."
        fi
    fi
done < <(list_cpp_files)

pass "CHECK 4 done"
echo

# =============================================================================
# CHECK 5: REST API POST/PATCH/DELETE handlers have CheckBodySize
#
# Every HTTP handler lambda that reads the request body via BodyToString()
# must call BanJson::CheckBodySize(Req) first to return HTTP 413 rather
# than silently treating an oversized body as empty JSON.
# =============================================================================
echo "--- CHECK 5: CheckBodySize present in all body-reading REST handlers ---"

while IFS= read -r -d '' file; do
    if grep -qP 'BodyToString' "$file"; then
        body_count=$(grep -cP 'BodyToString' "$file")
        check_count=$(grep -cP 'CheckBodySize' "$file")
        # Each BodyToString site should have a corresponding CheckBodySize.
        # We use a simple count heuristic; if counts differ, flag for review.
        if [[ "$check_count" -lt "$body_count" ]]; then
            fail "CHECK 5 – CheckBodySize coverage" \
                "File: $file" \
                "BodyToString() called $body_count time(s) but CheckBodySize() only $check_count time(s)." \
                "Fix: add 'if (auto SizeErr = BanJson::CheckBodySize(Req)) { Done(MoveTemp(SizeErr)); return true; }' before each BodyToString call."
        fi
    fi
done < <(list_cpp_files)

pass "CHECK 5 done"
echo

# =============================================================================
# CHECK 6: FCriticalSection / FScopeLock present in all registry classes
#          that have shared mutable state and are accessed from multiple threads
#
# Only flag classes whose names end in "Registry" or "Database" or "Log" —
# these are the subsystems that are explicitly designed to be thread-safe
# (they already use FScopeLock in their implementations).
# UObjects like BanEnforcer, BanDiscordSubsystem etc. are game-thread-only
# and intentionally do not use mutexes; they are excluded from this check.
# =============================================================================
echo "--- CHECK 6: FCriticalSection present in thread-safe registry/database headers ---"

while IFS= read -r -d '' file; do
    # Only scan headers whose filename matches the thread-safe registry pattern.
    basename="$(basename "$file" .h)"
    if [[ "$basename" =~ Registry$|Database$|Log$ ]]; then
        has_container=$(grep -cP '\bTMap\b|\bTArray\b|\bTSet\b' "$file")
        has_mutex=$(grep -cP '\bFCriticalSection\b|\bFRWLock\b' "$file")
        if [[ "$has_container" -gt 0 && "$has_mutex" -eq 0 ]]; then
            fail "CHECK 6 – missing FCriticalSection" \
                "File: $file" \
                "Registry/Database/Log class declares TMap/TArray/TSet but has no FCriticalSection or FRWLock." \
                "Fix: add 'mutable FCriticalSection Mutex;' and use FScopeLock in every public method."
        fi
    fi
done < <(list_header_files)

pass "CHECK 6 done"
echo

# =============================================================================
# CHECK 7: Double-fragment size check before MoveTemp (WebSocket server)
#
# In SMLWebSocketServerRunnable.cpp the oversized-fragment check must appear
# BEFORE the MoveTemp(Payload) that consumes the data.  If the check comes
# after MoveTemp, the payload is already destroyed when we try to reject it.
# =============================================================================
echo "--- CHECK 7: Fragment size check before MoveTemp in WebSocket server ---"

SERVER_RUNNABLE="$MOD_ROOT/SMLWebSocket/Source/SMLWebSocket/Private/SMLWebSocketServerRunnable.cpp"
if [[ -f "$SERVER_RUNNABLE" ]]; then
    # Get line numbers for the size check and the MoveTemp.
    size_line=$(grep -n 'MaxMessageBytes\|MaxFrameSize\|too large\|oversized\|MaxPayload' "$SERVER_RUNNABLE" | head -1 | cut -d: -f1)
    move_line=$(grep -n 'MoveTemp.*Payload\|FragmentBuffer.*MoveTemp' "$SERVER_RUNNABLE" | head -1 | cut -d: -f1)
    if [[ -n "$size_line" && -n "$move_line" ]]; then
        if [[ "$size_line" -gt "$move_line" ]]; then
            fail "CHECK 7 – size check after MoveTemp" \
                "File: $SERVER_RUNNABLE" \
                "Size check (line $size_line) comes AFTER MoveTemp (line $move_line)." \
                "Fix: move the size check above the MoveTemp(Payload) call."
        fi
    fi
fi

pass "CHECK 7 done"
echo

# =============================================================================
# CHECK 8: static_cast<int32> from float/double without range guard
#
# Casting an unbounded float/double to int32 is UB when the value is outside
# [INT32_MIN, INT32_MAX].  Every static_cast<int32>() applied to a float or
# the result of a floating-point function (GetIniFloat, etc.) must be wrapped
# in a clamping helper or explicit range check.
# =============================================================================
echo "--- CHECK 8: static_cast<int32> from float/double without range guard ---"

while IFS= read -r -d '' file; do
    # Look for direct static_cast<int32>(GetIniFloat or similar float source).
    if grep -qP 'static_cast<int32>\s*\(\s*(GetIniFloat|GetFloat|\.GetFloat|[0-9]+\.[0-9]+f?)' "$file"; then
        fail "CHECK 8 – unsafe float-to-int32 cast" \
            "File: $file" \
            "static_cast<int32> applied to a float/GetIniFloat result without range guard." \
            "Fix: use a helper like GetIniInt() that clamps before casting."
        grep -nP 'static_cast<int32>\s*\(\s*(GetIniFloat|GetFloat|\.GetFloat)' "$file" | while IFS= read -r ln; do
            echo "       Line: $ln"
        done
    fi
done < <(list_cpp_files)

pass "CHECK 8 done"
echo

# =============================================================================
# CHECK 9: Integer overflow in duration arithmetic (ban/mute parsing)
#
# Duration parsers that do "Total += Num * Multiplier" (or similar literal
# multipliers like 10080/1440/60) can overflow int64 when user input is very
# large.  Each multiplication must be preceded by an INT64_MAX / Multiplier
# guard AND the digit-accumulation loop must also guard against overflow.
#
# We detect the pattern by looking for unguarded "Num * 10080" style literals
# without a corresponding INT64_MAX guard present anywhere in the same file.
# BanChatCommands.cpp was fixed with explicit per-multiplier guards; we verify
# all other duration parsers are equally protected.
# =============================================================================
echo "--- CHECK 9: Overflow guards in duration arithmetic ---"

while IFS= read -r -d '' file; do
    # Check for the literal multiplier pattern (week/day/hour in minutes).
    if grep -qP 'Num\s*\*\s*(10080|1440|3600|86400)\b' "$file"; then
        # The file must have at least one INT64_MAX guard for the multiplication.
        if ! grep -qP 'INT64_MAX\s*/\s*(Multiplier|multiplier|10080|1440|3600|86400)' "$file"; then
            fail "CHECK 9 – duration multiplication overflow" \
                "File: $file" \
                "Has 'Num * <week/day/hour multiplier>' without INT64_MAX / Multiplier overflow guard." \
                "Fix: add 'if (Multiplier > 1 && Num > INT64_MAX / Multiplier) return 0/−1;' before each multiply."
        fi
    fi
done < <(list_cpp_files)

pass "CHECK 9 done"
echo

# =============================================================================
# CHECK 10: JSON parse root validated before use
#
# Every FJsonSerializer::Deserialize call must check both the bool return AND
# Root.IsValid() before accessing Root->...  A missing check leads to a null
# dereference when JSON input is malformed.
# =============================================================================
echo "--- CHECK 10: JSON parse results validated before use ---"

while IFS= read -r -d '' file; do
    # Count Deserialize calls vs. IsValid() checks in the same file.
    deser_count=$(grep -cP 'FJsonSerializer::Deserialize' "$file")
    valid_count=$(grep -cP '\.IsValid\(\)' "$file")
    if [[ "$deser_count" -gt 0 && "$valid_count" -lt "$deser_count" ]]; then
        fail "CHECK 10 – JSON parse not fully validated" \
            "File: $file" \
            "FJsonSerializer::Deserialize called $deser_count time(s) but IsValid() only $valid_count time(s)." \
            "Fix: every Deserialize call site must check '|| !Root.IsValid()'."
    fi
done < <(list_cpp_files)

pass "CHECK 10 done"
echo

# =============================================================================
# CHECK 11: FCString::Atoi (int32) without a Len <= guard
#
# FCString::Atoi silently overflows when the string is longer than 10 digits
# (INT32_MAX has 10 digits).  Every file that calls FCString::Atoi — as
# opposed to FCString::Atoi64 — must also have at least one ".Len() <="
# check to reject strings that are too long before converting them.
#
# Note: FCString::Atoi64 has its own separate check (CHECK 13).
# =============================================================================
echo "--- CHECK 11: FCString::Atoi (int32) guarded by Len() <= check ---"

while IFS= read -r -d '' file; do
    # Does this file have a real (non-comment) FCString::Atoi call (not Atoi64)?
    # Pipeline: grep all Atoi lines, then discard pure-comment lines.
    atoi_lines=$(grep -P '\bFCString::Atoi\b(?!64)' "$file" | grep -vP '^\s*//')
    if [[ -n "$atoi_lines" ]]; then
        # Accept either .Len() or ->Len() paired with any comparison operator (<, >, <=, >=).
        if ! grep -qP '(?:\.|->)Len\(\)\s*[<>!]' "$file"; then
            fail "CHECK 11 – FCString::Atoi without Len() guard" \
                "File: $file" \
                "Calls FCString::Atoi (int32) but has no Len() length-guard." \
                "Fix: add 'if (!Str.IsNumeric() || Str.Len() > 10 || (Str.Len() == 10 && Str > TEXT(\"2147483647\"))) return Default;' before each Atoi call."
            echo "$atoi_lines" | while IFS= read -r ln; do
                echo "       Line: $ln"
            done
        fi
    fi
done < <(list_cpp_files)

pass "CHECK 11 done"
echo

# =============================================================================
# CHECK 12: FCString::Atof result guarded with FMath::IsFinite
#
# FCString::Atof can return NaN or ±Infinity for inputs like "nan", "inf",
# or extremely large exponents.  Every file that calls FCString::Atof must
# also call FMath::IsFinite on the result before using it, to prevent NaN
# or Inf from propagating into configuration values, ban durations, or
# arithmetic expressions.
# =============================================================================
echo "--- CHECK 12: FCString::Atof result guarded with FMath::IsFinite ---"

while IFS= read -r -d '' file; do
    if grep -qP '\bFCString::Atof\b' "$file"; then
        if ! grep -qP '\bFMath::IsFinite\b' "$file"; then
            fail "CHECK 12 – FCString::Atof without FMath::IsFinite guard" \
                "File: $file" \
                "Calls FCString::Atof but has no FMath::IsFinite guard on the result." \
                "Fix: add 'return FMath::IsFinite(Result) ? Result : Default;' after each Atof call."
            grep -nP '\bFCString::Atof\b' "$file" | while IFS= read -r ln; do
                echo "       Line: $ln"
            done
        fi
    fi
done < <(list_cpp_files)

pass "CHECK 12 done"
echo

# =============================================================================
# CHECK 13: FCString::Atoi64 (int64) without IsNumeric() and Len() <= guard
#
# FCString::Atoi64 overflows for strings exceeding INT64_MAX (19 digits).
# Every file that calls FCString::Atoi64 must have BOTH:
#   1. An IsNumeric() check — to reject non-digit strings.
#   2. A Len() <= check  — to reject strings longer than 19 characters.
# The lexicographic overflow guard (comparing to "9223372036854775807") is
# encouraged but not required by this check; the two guards above are the
# minimum mandatory protection.
# =============================================================================
echo "--- CHECK 13: FCString::Atoi64 guarded by IsNumeric() and Len() <= ---"

while IFS= read -r -d '' file; do
    if grep -qP '\bFCString::Atoi64\b' "$file"; then
        # Accept either .IsNumeric() or FChar::IsDigit as a character-validity guard.
        has_isnumeric=$(grep -cP '\.IsNumeric\(\)|FChar::IsDigit' "$file")
        # Accept .Len() or ->Len() followed by any comparison operator (<, >, <=, >=, ==, !=).
        has_len=$(grep -cP '(?:\.|->)Len\(\)\s*[<>!]' "$file")
        if [[ "$has_isnumeric" -eq 0 || "$has_len" -eq 0 ]]; then
            fail "CHECK 13 – FCString::Atoi64 without full safety guard" \
                "File: $file" \
                "Calls FCString::Atoi64 but is missing IsNumeric()/IsDigit guard (count=$has_isnumeric) or Len() comparison guard (count=$has_len)." \
                "Fix: add 'if (!Str.IsNumeric() || Str.Len() > 19 || (Str.Len() == 19 && Str > TEXT(\"9223372036854775807\"))) return Default;' before each Atoi64 call."
            grep -nP '\bFCString::Atoi64\b' "$file" | while IFS= read -r ln; do
                echo "       Line: $ln"
            done
        fi
    fi
done < <(list_cpp_files)

pass "CHECK 13 done"
echo

# =============================================================================
# CHECK 14: AsyncTask lambdas must capture UObjects via TWeakObjectPtr
#
# Lambdas passed to AsyncTask run on a background thread and may execute
# after the owning UObject has been garbage-collected.  Capturing a raw
# UObject pointer (e.g. "this" or a member pointer) in such a lambda is a
# use-after-free.  Every file that uses AsyncTask must also use the
# TWeakObjectPtr (or WeakThis / WeakOwner) capture pattern to guard against
# accessing a destroyed object.
# =============================================================================
echo "--- CHECK 14: AsyncTask lambdas capture UObjects via TWeakObjectPtr ---"

while IFS= read -r -d '' file; do
    if grep -qP '\bAsyncTask\b' "$file"; then
        if ! grep -qP '\bTWeakObjectPtr\b|\bWeakThis\b|\bWeakOwner\b|\bWeakGI\b' "$file"; then
            fail "CHECK 14 – AsyncTask without TWeakObjectPtr capture" \
                "File: $file" \
                "Uses AsyncTask but has no TWeakObjectPtr/WeakThis guard for captured UObjects." \
                "Fix: capture UObject* as 'TWeakObjectPtr<T> WeakX = this;' and check '.IsValid()' before use inside the lambda."
        fi
    fi
done < <(list_cpp_files)

pass "CHECK 14 done"
echo

# =============================================================================
# CHECK 15: PathParams uid values must be URL-decoded before use
#
# UE's HTTP server does NOT automatically URL-decode path parameter values.
# A UID like "EOS:abc%3Axyz" will arrive with the '%3A' still encoded.
# Every file that reads a uid path parameter via PathParams.FindRef("uid")
# must also call FGenericPlatformHttp::UrlDecode() on the raw value before
# passing it to database lookups or string comparisons.
# =============================================================================
echo "--- CHECK 15: PathParams uid values URL-decoded before use ---"

while IFS= read -r -d '' file; do
    if grep -qP 'PathParams.*\buid\b' "$file"; then
        if ! grep -qP '\bUrlDecode\b' "$file"; then
            fail "CHECK 15 – PathParams uid not URL-decoded" \
                "File: $file" \
                "Reads uid from PathParams but has no UrlDecode() call." \
                "Fix: add 'const FString Uid = FGenericPlatformHttp::UrlDecode(RawUid);' after PathParams.FindRef(\"uid\")."
        fi
    fi
done < <(list_cpp_files)

pass "CHECK 15 done"
echo

# =============================================================================
# CHECK 16: Signed numeric validation must not allow '-' in non-leading positions
#
# Pattern to reject:
#   if (!FChar::IsDigit(Ch) && Ch != TEXT('-')) { ... }
# This accepts malformed values like "12-3", which then reach FCString::Atoi64
# and can be misparsed.  Signed integer validators must only allow an optional
# single leading '-' and require all remaining characters to be digits.
# =============================================================================
echo "--- CHECK 16: Signed numeric validation rejects interior '-' characters ---"

while IFS= read -r -d '' file; do
    if grep -qP '!\s*FChar::IsDigit\([^)]*\)\s*&&\s*[^;]*!=\s*TEXT\((?:\x27-\x27|\x22-\x22)\)' "$file"; then
        fail "CHECK 16 – permissive signed-number validator" \
            "File: $file" \
            "Uses '!FChar::IsDigit(...) && ... != TEXT('-')' style validation, which allows '-' in non-leading positions." \
            "Fix: validate as optional leading '-' only, then require digits for every remaining character."
        grep -nP '!\s*FChar::IsDigit\([^)]*\)\s*&&\s*[^;]*!=\s*TEXT\((?:\x27-\x27|\x22-\x22)\)' "$file" | while IFS= read -r ln; do
            echo "       Line: $ln"
        done
    fi
done < <(list_cpp_files)

pass "CHECK 16 done"
echo

# =============================================================================
# CHECK 17: EscapeMarkdown applied to Uid in all Discord embed Field() calls
#
# Every user-controlled string in a Discord embed must go through EscapeMarkdown
# before being placed in a Field() call.  The Uid (compound UID) is user-
# controlled (includes "IP:" prefixes with caller-supplied values) and must be
# escaped just like PlayerName, Reason, etc.
# =============================================================================
echo "--- CHECK 17: EscapeMarkdown applied to Uid in Discord embed Field() calls ---"

while IFS= read -r -d '' file; do
    # Look for Field(...Uid...) patterns where EscapeMarkdown is absent
    if grep -qP 'Field\s*\(\s*TEXT\s*\(\s*"UID"\s*\)\s*,\s*(?!EscapeMarkdown)[A-Za-z]' "$file"; then
        fail "CHECK 17 – raw Uid in Discord embed Field()" \
            "File: $file" \
            "A Field(TEXT(\"UID\"), ...) call passes a raw string without EscapeMarkdown()." \
            "Fix: wrap the value with EscapeMarkdown(...)."
        grep -nP 'Field\s*\(\s*TEXT\s*\(\s*"UID"\s*\)\s*,\s*(?!EscapeMarkdown)[A-Za-z]' "$file" | while IFS= read -r ln; do
            echo "       Line: $ln"
        done
    fi
done < <(list_cpp_files)

pass "CHECK 17 done"
echo

# =============================================================================
# CHECK 18: EAppealStatus::Dismissed is declared in BanTypes.h
#
# The codebase uses EAppealStatus::Dismissed in multiple call sites.  If the
# enum value is not declared the project will not compile.
# =============================================================================
echo "--- CHECK 18: EAppealStatus::Dismissed declared in BanTypes.h ---"

BANTYPES_H="$(find "$REPO_ROOT" -name BanTypes.h -path '*/BanSystem/*' | head -1)"
if [[ -z "$BANTYPES_H" ]]; then
    fail "CHECK 18 – BanTypes.h not found" \
        "Expected file: Mods/BanSystem/Source/BanSystem/Public/BanTypes.h" \
        "BanTypes.h could not be located in the repository."
elif ! grep -q 'Dismissed' "$BANTYPES_H"; then
    fail "CHECK 18 – EAppealStatus::Dismissed missing from BanTypes.h" \
        "File: $BANTYPES_H" \
        "EAppealStatus::Dismissed is used across the codebase but is not declared in the enum." \
        "Fix: add 'Dismissed UMETA(DisplayName = \"Dismissed\"),' to EAppealStatus."
fi

pass "CHECK 18 done"
echo

# =============================================================================
# CHECK 19: AppealToJson() must handle EAppealStatus::Dismissed
#
# AppealToJson() serializes FBanAppealEntry to JSON for every REST endpoint
# that returns appeal records.  If the Dismissed case is absent from the
# switch the status is silently serialized as "pending", misleading API
# consumers and any downstream tooling.
# =============================================================================
echo "--- CHECK 19: AppealToJson() handles EAppealStatus::Dismissed ---"

RESTAPI_CPP="$(find "$REPO_ROOT" -name BanRestApi.cpp -path '*/BanSystem/*' | head -1)"
if [[ -z "$RESTAPI_CPP" ]]; then
    fail "CHECK 19 – BanRestApi.cpp not found" \
        "Expected file: Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp"
else
    # Check for 'case EAppealStatus::Dismissed: StatusStr = TEXT("dismissed");' in AppealToJson
    if ! grep -qP 'case\s+EAppealStatus::Dismissed\s*:\s*StatusStr\s*=\s*TEXT\s*\(\s*"dismissed"\s*\)' "$RESTAPI_CPP"; then
        fail "CHECK 19 – AppealToJson() missing Dismissed→\"dismissed\" mapping" \
            "File: $RESTAPI_CPP" \
            "AppealToJson() does not map EAppealStatus::Dismissed to the JSON string \"dismissed\"." \
            "Fix: add 'case EAppealStatus::Dismissed: StatusStr = TEXT(\"dismissed\"); break;' to the switch."
    fi
fi

pass "CHECK 19 done"
echo

# =============================================================================
# CHECK 20: GET /appeals status filter must recognise "dismissed"
#
# The ?status= query-parameter filter in the GET /appeals REST handler must
# map the string "dismissed" to EAppealStatus::Dismissed.  Without this,
# ?status=dismissed silently returns Pending appeals instead.
# =============================================================================
echo "--- CHECK 20: GET /appeals status filter maps \"dismissed\" ---"

if [[ -z "$RESTAPI_CPP" ]]; then
    fail "CHECK 20 – BanRestApi.cpp not found" \
        "Expected file: Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp"
else
    # Check for 'else if (Norm == TEXT("dismissed")) FilterStatus = EAppealStatus::Dismissed;'
    if ! grep -qP 'Norm\s*==\s*TEXT\s*\(\s*"dismissed"\s*\)\s*\)\s*FilterStatus\s*=\s*EAppealStatus::Dismissed' "$RESTAPI_CPP"; then
        fail "CHECK 20 – GET /appeals filter missing \"dismissed\" mapping" \
            "File: $RESTAPI_CPP" \
            "The ?status= filter does not handle \"dismissed\", so ?status=dismissed returns wrong results." \
            "Fix: add 'else if (Norm == TEXT(\"dismissed\")) FilterStatus = EAppealStatus::Dismissed;' to the filter."
    fi
fi

pass "CHECK 20 done"
echo

# =============================================================================
# CHECK 21: /history command uses W.Id (persistent warning ID) not i+1
#
# The /history chat command must display the persistent database primary key
# (W.Id, an int64) as the warning number, not a transient loop counter.
# Using i+1 produces fake numbers that do not match the IDs required by
# /clearwarn, causing player confusion and inability to clear specific warnings.
# =============================================================================
echo "--- CHECK 21: /history command uses W.Id, not loop counter i+1 ---"

BANCHATCHMDS_CPP="$(find "$REPO_ROOT" -name BanChatCommands.cpp -path '*/BanChatCommands/*' | head -1)"
if [[ -z "$BANCHATCHMDS_CPP" ]]; then
    fail "CHECK 21 – BanChatCommands.cpp not found" \
        "Expected file: Mods/BanChatCommands/Source/BanChatCommands/Private/Commands/BanChatCommands.cpp"
else
    # The /history loop must not use "i + 1" with %d as the displayed warning number in a Printf
    if grep -qP 'FString::Printf\s*\(\s*TEXT\s*\([^)]*#%d[^)]*\)[^,]*,\s*i\s*\+\s*1\s*,' "$BANCHATCHMDS_CPP"; then
        fail "CHECK 21 – /history displays loop counter i+1 instead of W.Id" \
            "File: $BANCHATCHMDS_CPP" \
            "The warning display loop uses 'i + 1' as the displayed ID, not the persistent W.Id." \
            "Fix: replace '#%d ... i + 1' with '#%lld ... W.Id'."
        grep -nP 'FString::Printf\s*\(\s*TEXT\s*\([^)]*#%d[^)]*\)[^,]*,\s*i\s*\+\s*1\s*,' "$BANCHATCHMDS_CPP" | while IFS= read -r ln; do
            echo "       Line: $ln"
        done
    fi
fi

pass "CHECK 21 done"
echo

# =============================================================================
# CHECK 22: RemoveBanByUid/RemoveBanById rolls back in-memory removal on save failure
# =============================================================================
echo "--- CHECK 22: BanDatabase rolls back Bans entry on SaveToFile failure ---"
BANDB_CPP="$(find "$REPO_ROOT" -name BanDatabase.cpp -path '*/BanSystem/*' | head -1)"
if [[ -z "$BANDB_CPP" ]]; then
    fail "CHECK 22 – BanDatabase.cpp not found"
else
    # The rollback inserts the captured OutEntry back via Bans.Add(OutEntry).
    if ! grep -qP 'Bans\.Add\s*\(\s*OutEntry\s*\)' "$BANDB_CPP"; then
        fail "CHECK 22 – RemoveBanByUid/RemoveBanById does not roll back Bans on SaveToFile failure" \
            "File: $BANDB_CPP" \
            "When SaveToFile fails after Bans.RemoveAll, the entry must be re-inserted: Bans.Add(OutEntry)."
    fi
fi
pass "CHECK 22 done"
echo

# =============================================================================
# CHECK 23: AddBan/AddBanSkipIfPermanentExists rolls back in-memory addition on save failure
# =============================================================================
echo "--- CHECK 23: BanDatabase rolls back Bans entry on AddBan SaveToFile failure ---"
if [[ -z "$BANDB_CPP" ]]; then
    fail "CHECK 23 – BanDatabase.cpp not found"
else
    # The rollback removes the ghost entry via Bans.RemoveAll([&NewEntry]...).
    if ! grep -qP 'Bans\.RemoveAll\s*\(\s*\[&NewEntry\]' "$BANDB_CPP"; then
        fail "CHECK 23 – AddBan/AddBanSkipIfPermanentExists does not roll back Bans on SaveToFile failure" \
            "File: $BANDB_CPP" \
            "When SaveToFile fails after Bans.Add(NewEntry), the entry must be removed: Bans.RemoveAll([&NewEntry]...)."
    fi
fi
pass "CHECK 23 done"
echo

# =============================================================================
# CHECK 24: RestApiRemoveCounterpartBans fires NotifyBanRemoved for each counterpart
# =============================================================================
echo "--- CHECK 24: RestApiRemoveCounterpartBans fires NotifyBanRemoved per counterpart ---"
BANREST_CPP="$(find "$REPO_ROOT" -name BanRestApi.cpp -path '*/BanSystem/*' | head -1)"
if [[ -z "$BANREST_CPP" ]]; then
    fail "CHECK 24 – BanRestApi.cpp not found"
else
    # Verify NotifyBanRemoved is called with LinkedUid inside RestApiRemoveCounterpartBans.
    if ! grep -qP 'NotifyBanRemoved\s*\(\s*LinkedUid' "$BANREST_CPP"; then
        fail "CHECK 24 – RestApiRemoveCounterpartBans does not call NotifyBanRemoved for linked counterparts" \
            "File: $BANREST_CPP" \
            "Each successful RemoveBanByUid in RestApiRemoveCounterpartBans must be followed by NotifyBanRemoved."
    fi
fi
pass "CHECK 24 done"
echo

# =============================================================================
# CHECK 25: MuteRegistry::GetRegistryPath() respects UBanSystemConfig::DatabasePath
# =============================================================================
echo "--- CHECK 25: MuteRegistry::GetRegistryPath() respects DatabasePath ---"
MUTEREG_CPP="$(find "$REPO_ROOT" -name MuteRegistry.cpp -path '*/BanChatCommands/*' | head -1)"
if [[ -z "$MUTEREG_CPP" ]]; then
    fail "CHECK 25 – MuteRegistry.cpp not found"
else
    # The fix reads Cfg->DatabasePath inside GetRegistryPath.
    if ! grep -qP 'Cfg\s*->\s*DatabasePath' "$MUTEREG_CPP"; then
        fail "CHECK 25 – MuteRegistry::GetRegistryPath() is hardcoded; it ignores UBanSystemConfig::DatabasePath" \
            "File: $MUTEREG_CPP" \
            "GetRegistryPath() must read Cfg->DatabasePath like other registries."
    fi
fi
pass "CHECK 25 done"
echo

# =============================================================================
# CHECK 26: PlayerNoteRegistry::GetRegistryPath() respects UBanSystemConfig::DatabasePath
# =============================================================================
echo "--- CHECK 26: PlayerNoteRegistry::GetRegistryPath() respects DatabasePath ---"
NOTEREG_CPP="$(find "$REPO_ROOT" -name PlayerNoteRegistry.cpp -path '*/BanChatCommands/*' | head -1)"
if [[ -z "$NOTEREG_CPP" ]]; then
    fail "CHECK 26 – PlayerNoteRegistry.cpp not found"
else
    if ! grep -qP 'Cfg\s*->\s*DatabasePath' "$NOTEREG_CPP"; then
        fail "CHECK 26 – PlayerNoteRegistry::GetRegistryPath() is hardcoded; it ignores UBanSystemConfig::DatabasePath" \
            "File: $NOTEREG_CPP" \
            "GetRegistryPath() must read Cfg->DatabasePath like other registries."
    fi
fi
pass "CHECK 26 done"
echo

# =============================================================================
# CHECK 27: AddWarning(FWarningEntry) only stamps WarnDate when caller left it default
# =============================================================================
echo "--- CHECK 27: AddWarning(FWarningEntry) preserves caller-supplied WarnDate ---"
WARNREG_CPP="$(find "$REPO_ROOT" -name PlayerWarningRegistry.cpp -path '*/BanSystem/*' | head -1)"
if [[ -z "$WARNREG_CPP" ]]; then
    fail "CHECK 27 – PlayerWarningRegistry.cpp not found"
else
    # The fix guards the WarnDate stamp with: if (Entry.WarnDate == FDateTime(0))
    if ! grep -qP 'WarnDate\s*==\s*FDateTime\s*\(\s*0\s*\)' "$WARNREG_CPP"; then
        fail "CHECK 27 – AddWarning(FWarningEntry) unconditionally overwrites caller's WarnDate" \
            "File: $WARNREG_CPP" \
            "The struct overload must only set WarnDate = UtcNow() when Entry.WarnDate == FDateTime(0)."
    fi
fi
pass "CHECK 27 done"
echo

# =============================================================================
# CHECK 28: wl_approve button does not grant access when WhitelistCommandRoleId is empty
# =============================================================================
echo "--- CHECK 28: wl_approve button bHasRole not initialised from empty role ---"
DBS_CPP="$(find "$REPO_ROOT" -name DiscordBridgeSubsystem.cpp -path '*/DiscordBridge/*' | head -1)"
if [[ -z "$DBS_CPP" ]]; then
    fail "CHECK 28 – DiscordBridgeSubsystem.cpp not found"
else
    # Negative: old vulnerable pattern must be absent.
    if grep -qP 'bHasRole\s*=\s*WhitelistConfig\.WhitelistCommandRoleId\.IsEmpty\(\)' "$DBS_CPP"; then
        fail "CHECK 28 – wl_approve handler sets bHasRole=true when WhitelistCommandRoleId is empty" \
            "File: $DBS_CPP" \
            "Change 'bHasRole = WhitelistConfig.WhitelistCommandRoleId.IsEmpty()' to 'bHasRole = false'."
    fi
fi
pass "CHECK 28 done"
echo

# =============================================================================
# CHECK 29: GET /notes serialises actual note entries (not just count)
# =============================================================================
echo "--- CHECK 29: GET /notes serialises note entries via reflection ---"
if [[ -z "$BANREST_CPP" ]]; then
    fail "CHECK 29 – BanRestApi.cpp not found"
else
    # Verify the handler uses FScriptArrayHelper to iterate entries and
    # FStructProperty to access the inner struct.
    if ! grep -qP 'CastField\s*<\s*FStructProperty\s*>\s*\(\s*NotesProp\s*->\s*Inner\s*\)' "$BANREST_CPP"; then
        fail "CHECK 29 – GET /notes always returns an empty notes array" \
            "File: $BANREST_CPP" \
            "The handler must iterate NotesProp entries via FScriptArrayHelper and read fields via CastField<FStructProperty>(NotesProp->Inner)."
    fi
fi
pass "CHECK 29 done"
echo

# =============================================================================
# CHECK 30: Loader paths reject non-positive persisted IDs
# =============================================================================
echo "--- CHECK 30: persisted IDs are validated as > 0 on load ---"
AUDITLOG_CPP="$(find "$REPO_ROOT" -name BanAuditLog.cpp -path '*/BanSystem/*' | head -1)"
WARNREG_CPP_CHECK30="$(find "$REPO_ROOT" -name PlayerWarningRegistry.cpp -path '*/BanSystem/*' | head -1)"
SCHEDREG_CPP="$(find "$REPO_ROOT" -name ScheduledBanRegistry.cpp -path '*/BanSystem/*' | head -1)"
BANDB_CPP_CHECK30="$(find "$REPO_ROOT" -name BanDatabase.cpp -path '*/BanSystem/*' | head -1)"
TICKETSUB_CPP="$(find "$REPO_ROOT" -name TicketSubsystem.cpp -path '*/DiscordBridge/*' | head -1)"

if [[ -z "$AUDITLOG_CPP" ]]; then
    fail "CHECK 30 – BanAuditLog.cpp not found"
elif ! grep -qP 'Entry\.Id\s*<=\s*0' "$AUDITLOG_CPP"; then
    fail "CHECK 30 – BanAuditLog accepts non-positive entry IDs from disk" \
        "File: $AUDITLOG_CPP" \
        "LoadFromFile() should skip entries when Entry.Id <= 0."
fi

if [[ -z "$WARNREG_CPP_CHECK30" ]]; then
    fail "CHECK 30 – PlayerWarningRegistry.cpp not found"
elif ! grep -qP 'Entry\.Id\s*<=\s*0' "$WARNREG_CPP_CHECK30"; then
    fail "CHECK 30 – PlayerWarningRegistry accepts non-positive warning IDs from disk" \
        "File: $WARNREG_CPP_CHECK30" \
        "LoadFromFile() should skip warnings when Entry.Id <= 0."
fi

if [[ -z "$SCHEDREG_CPP" ]]; then
    fail "CHECK 30 – ScheduledBanRegistry.cpp not found"
elif ! grep -qP 'Entry\.Id\s*<=\s*0' "$SCHEDREG_CPP"; then
    fail "CHECK 30 – ScheduledBanRegistry accepts non-positive scheduled-ban IDs from disk" \
        "File: $SCHEDREG_CPP" \
        "LoadFromFile() should skip entries when Entry.Id <= 0."
fi

if [[ -z "$BANDB_CPP_CHECK30" ]]; then
    fail "CHECK 30 – BanDatabase.cpp not found"
elif ! grep -qP 'OutEntry\.Id\s*>\s*0' "$BANDB_CPP_CHECK30"; then
    fail "CHECK 30 – BanDatabase::JsonToEntry does not require positive IDs" \
        "File: $BANDB_CPP_CHECK30" \
        "JsonToEntry() should reject entries unless OutEntry.Id > 0."
fi

if [[ -z "$TICKETSUB_CPP" ]]; then
    fail "CHECK 30 – TicketSubsystem.cpp not found"
elif ! grep -qP 'ParsedAppealId\s*>\s*0' "$TICKETSUB_CPP"; then
    fail "CHECK 30 – TicketSubsystem restores non-positive appeal IDs from ticket state" \
        "File: $TICKETSUB_CPP" \
        "State restore should add OpenerToAppealId only when ParsedAppealId > 0."
fi

pass "CHECK 30 done"
echo

# =============================================================================
# CHECK 31: GET /notes serialises note IDs as string, not double
#
# int64 IDs cast to double lose precision for values > 2^53.  The fix is to use
# SetStringField(TEXT("id"), FString::Printf(TEXT("%lld"), IdVal)) matching the
# convention used for all other IDs in the REST API.
# =============================================================================
echo "--- CHECK 31: GET /notes serialises note IDs as decimal string not double ---"

BANRESTAPI_CPP_CHECK31="$(list_cpp_files | tr '\0' '\n' | grep 'BanRestApi\.cpp' | head -1)"

if [[ -z "$BANRESTAPI_CPP_CHECK31" ]]; then
    fail "CHECK 31 – BanRestApi.cpp not found"
elif grep -qP 'SetNumberField\s*\(\s*TEXT\s*\(\s*"id"\s*\)' "$BANRESTAPI_CPP_CHECK31"; then
    fail "CHECK 31 – GET /notes serialises note ID as double (precision loss for id > 2^53)" \
        "File: $BANRESTAPI_CPP_CHECK31" \
        "Use SetStringField(TEXT(\"id\"), FString::Printf(TEXT(\"%lld\"), IdVal)) instead."
fi

pass "CHECK 31 done"
echo

# =============================================================================
# CHECK 32: BanSyncClient skips NotifyBanCreated for peer ban updates
#
# When a peer sync message updates an existing ban (bWasUpdate=true), firing
# NotifyBanCreated posts a spurious "🔨 Player Banned" webhook for what was
# merely a reason/duration edit.  The guard "if (!bWasUpdate)" must be present.
# =============================================================================
echo "--- CHECK 32: BanSyncClient skips NotifyBanCreated for peer ban updates ---"

BANSYNC_CPP_CHECK32="$(list_cpp_files | tr '\0' '\n' | grep 'BanSyncClient\.cpp' | head -1)"

if [[ -z "$BANSYNC_CPP_CHECK32" ]]; then
    fail "CHECK 32 – BanSyncClient.cpp not found"
elif ! grep -qP 'bWasUpdate' "$BANSYNC_CPP_CHECK32"; then
    fail "CHECK 32 – BanSyncClient does not track bWasUpdate for peer ban updates" \
        "File: $BANSYNC_CPP_CHECK32" \
        "Set bWasUpdate=true when RemoveBanByUid is called before re-adding and guard" \
        "NotifyBanCreated with 'if (!bWasUpdate)'."
elif ! grep -qP '!\s*bWasUpdate' "$BANSYNC_CPP_CHECK32"; then
    fail "CHECK 32 – BanSyncClient does not guard NotifyBanCreated with !bWasUpdate" \
        "File: $BANSYNC_CPP_CHECK32" \
        "NotifyBanCreated must be skipped when bWasUpdate is true."
fi

pass "CHECK 32 done"
echo

# =============================================================================
# CHECK 33: RemoveExpiredEntries clears the output array before appending
#
# Without OutExpiredNames.Reset() at the top, callers that reuse the array
# across multiple calls silently accumulate stale entries.
# =============================================================================
echo "--- CHECK 33: RemoveExpiredEntries clears output array before appending ---"

WLMGR_CPP_CHECK33="$(list_cpp_files | tr '\0' '\n' | grep 'WhitelistManager\.cpp' | head -1)"

if [[ -z "$WLMGR_CPP_CHECK33" ]]; then
    fail "CHECK 33 – WhitelistManager.cpp not found"
elif ! grep -qP 'OutExpiredNames\s*\.\s*(Reset|Empty)\s*\(' "$WLMGR_CPP_CHECK33"; then
    fail "CHECK 33 – RemoveExpiredEntries does not clear OutExpiredNames before appending" \
        "File: $WLMGR_CPP_CHECK33" \
        "Add OutExpiredNames.Reset() at the start of RemoveExpiredEntries."
fi

pass "CHECK 33 done"
echo

# =============================================================================
# CHECK 34: whitelist list / GetAll() / GetAllEntries() display code filters expired
#
# The whitelist list and groups commands call GetAllEntries() and must skip entries
# where ExpiresAt is set and <= UtcNow().  The GetAll() helper also must filter.
# =============================================================================
echo "--- CHECK 34: whitelist list/groups display filters expired entries ---"

WLMGR_CPP_CHECK34="$WLMGR_CPP_CHECK33"
DSUB_CPP_CHECK34="$(list_cpp_files | tr '\0' '\n' | grep 'DiscordBridgeSubsystem\.cpp' | head -1)"

if [[ -z "$WLMGR_CPP_CHECK34" ]]; then
    fail "CHECK 34 – WhitelistManager.cpp not found"
elif ! grep -qP 'ExpiresAt\s*<=\s*Now\w*' "$WLMGR_CPP_CHECK34"; then
    fail "CHECK 34 – GetAll() in WhitelistManager.cpp does not filter expired entries" \
        "File: $WLMGR_CPP_CHECK34" \
        "Skip entries where ExpiresAt.GetTicks() > 0 && ExpiresAt <= Now in GetAll()."
fi

if [[ -z "$DSUB_CPP_CHECK34" ]]; then
    fail "CHECK 34 – DiscordBridgeSubsystem.cpp not found"
elif ! grep -qP 'ExpiresAt\s*<=\s*Now\w*' "$DSUB_CPP_CHECK34"; then
    fail "CHECK 34 – whitelist list/groups in DiscordBridgeSubsystem.cpp do not filter expired entries" \
        "File: $DSUB_CPP_CHECK34" \
        "In 'whitelist list' and 'whitelist groups' skip entries where ExpiresAt <= Now."
fi

pass "CHECK 34 done"
echo


echo "========================================================"
if [[ "$ISSUES" -eq 0 ]]; then
    echo -e "${GRN}All checks passed — no issues found.${NC}"
    exit 0
else
    echo -e "${RED}${ISSUES} issue(s) found. Review the FAIL entries above.${NC}"
    exit 1
fi
