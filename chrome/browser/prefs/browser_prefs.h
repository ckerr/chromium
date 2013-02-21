// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PREFS_BROWSER_PREFS_H_
#define CHROME_BROWSER_PREFS_BROWSER_PREFS_H_

class PrefRegistrySimple;
class PrefRegistrySyncable;
class PrefService;
class Profile;

namespace chrome {

// Register all prefs that will be used via the local state PrefService.
void RegisterLocalState(PrefRegistrySimple* registry);

// Register all prefs that will be used via a PrefService attached to a Profile.
void RegisterUserPrefs(PrefService* user_prefs, PrefRegistrySyncable* registry);

// Migrates prefs from |local_state| to |profile|'s pref store.
void MigrateBrowserPrefs(Profile* profile, PrefService* local_state);

// Migrates prefs in |profile|'s pref store.
void MigrateUserPrefs(Profile* profile);

}  // namespace chrome

#endif  // CHROME_BROWSER_PREFS_BROWSER_PREFS_H_
