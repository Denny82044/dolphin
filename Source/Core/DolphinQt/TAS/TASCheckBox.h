// Copyright 2019 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QCheckBox>

#include "DolphinQt/TAS/TASControlState.h"

class QMouseEvent;
class TASInputWindow;

class TASCheckBox : public QCheckBox
{
  Q_OBJECT
public:
  explicit TASCheckBox(const QString& text, TASInputWindow* parent);

  // Can be called from the CPU thread
  bool GetValue() const;
  // Must be called from the CPU thread
  void OnControllerValueChanged(bool new_value);

protected:
  void mousePressEvent(QMouseEvent* event) override;

private slots:
#if QT_VERSION >= QT_VERSION_CHECK(6, 7, 0)
  void OnUIValueChanged(Qt::CheckState new_value);
#else
  void OnUIValueChanged(int new_value);
#endif
  void ApplyControllerValueChange();

private:
  const TASInputWindow* m_parent;
  TASControlState m_state;
  int m_frame_turbo_started = 0;
  // Poll-based turbo: counts controller polls (SI) instead of video frames, so presses can change
  // many times per frame (e.g. 1080Hz polling mods).
  bool m_turbo_use_polls = false;
  int m_turbo_channel = 0;
  u64 m_poll_turbo_started = 0;
  int m_turbo_press_frames = 0;
  int m_turbo_total_frames = 0;
};
