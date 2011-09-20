// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "webkit/glue/webkit_glue.h"

#include "base/base_paths.h"
#include "base/path_service.h"
#include "googleurl/src/gurl.h"
#include "webkit/glue/user_agent.h"
#include "webkit/plugins/npapi/plugin_list.h"

// Functions needed by webkit_glue.

namespace webkit_glue {

void GetPlugins(bool refresh,
                std::vector<webkit::WebPluginInfo>* plugins) {
  if (refresh)
    webkit::npapi::PluginList::Singleton()->RefreshPlugins();
  webkit::npapi::PluginList::Singleton()->GetPlugins(plugins);
  // Don't load the forked npapi_layout_test_plugin in DRT, we only want to
  // use the upstream version TestNetscapePlugIn.
  const FilePath::StringType kPluginBlackList[] = {
    FILE_PATH_LITERAL("npapi_layout_test_plugin.dll"),
    FILE_PATH_LITERAL("WebKitTestNetscapePlugIn.plugin"),
    FILE_PATH_LITERAL("libnpapi_layout_test_plugin.so"),
  };
  for (int i = plugins->size() - 1; i >= 0; --i) {
    webkit::WebPluginInfo plugin_info = plugins->at(i);
    for (size_t j = 0; j < arraysize(kPluginBlackList); ++j) {
      if (plugin_info.path.BaseName() == FilePath(kPluginBlackList[j])) {
        plugins->erase(plugins->begin() + i);
      }
    }
  }
}

void AppendToLog(const char*, int, const char*) {
}

bool IsProtocolSupportedForMedia(const GURL& url) {
  if (url.SchemeIsFile() ||
      url.SchemeIs("http") ||
      url.SchemeIs("https") ||
      url.SchemeIs("data"))
    return true;
  return false;
}

std::string BuildUserAgent(bool mimic_windows) {
  return webkit_glue::BuildUserAgentHelper(mimic_windows,
                                           "DumpRenderTree/0.0.0.0");
}

bool GetPluginFinderURL(std::string* plugin_finder_url) {
  return false;
}

#if defined(OS_WIN)
bool DownloadUrl(const std::string& url, HWND caller_window) {
  return false;
}
#endif

bool IsSingleProcess() {
  return true;
}

void EnableSpdy(bool enable) {
}

void UserMetricsRecordAction(const std::string& action) {
}

#if defined(OS_LINUX)
int MatchFontWithFallback(const std::string& face, bool bold,
                          bool italic, int charset) {
  return -1;
}

bool GetFontTable(int fd, uint32_t table, uint8_t* output,
                  size_t* output_length) {
  return false;
}
#endif

}  // namespace webkit_glue
