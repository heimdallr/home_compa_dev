object fmMain: TfmMain
  Left = 189
  Top = 108
  Width = 438
  Height = 385
  Caption = 'Just Another Tetris'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000000000000000000000000
    0000000080000080000000808000800000008000800080800000C0C0C0008080
    80000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF000000
    FFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF0000
    FFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF0000
    0000FFFF0000FFFFFFFFFFFF000000000000FFFF0000FFFFFFFFFFFF00000000
    0000FFFF0000FFFFFFFFFFFF000000000000FFFF0000FFFFFFFFFFFF00000000
    0000000000000000FFFF0000000000000000000000000000FFFF000000000000
    0000000000000000FFFF0000000000000000000000000000FFFF000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000FFFF0000000000000000000000000000FFFF000000000000000000000
    0000000FFFF0000000000000000000000000000FFFF000000000000000000000
    0000000FFFFFFFF000000000000000000000000FFFFFFFF00000000000000000
    0000000FFFFFFFF000000000000000000000000FFFFFFFF00000000000000000
    0000000FFFF0000000000000000000000000000FFFF000000000000000000000
    0000000FFFF0000000000000000000000000000FFFF000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  OldCreateOrder = False
  WindowState = wsMaximized
  OnPaint = FormPaint
  PixelsPerInch = 120
  TextHeight = 16
  object pnlImg: TPanel
    Left = 0
    Top = 0
    Width = 301
    Height = 357
    Align = alLeft
    BevelInner = bvRaised
    TabOrder = 0
    object imMain: TImage
      Left = 2
      Top = 2
      Width = 297
      Height = 353
      Align = alClient
    end
  end
  object pnlBottom: TPanel
    Left = 0
    Top = 357
    Width = 430
    Height = 0
    Align = alBottom
    BevelInner = bvRaised
    TabOrder = 1
  end
  object alMain: TActionList
    Left = 4
    Top = 4
    object actExit: TAction
      Caption = 'actExit'
      ShortCut = 32856
      OnExecute = actExitExecute
    end
    object actUp: TAction
      Caption = 'actUp'
      ShortCut = 38
      OnExecute = actMoveExecute
    end
    object actDown: TAction
      Tag = 1
      Caption = 'actDown'
      ShortCut = 40
      OnExecute = actMoveExecute
    end
    object actLeft: TAction
      Tag = 2
      Caption = 'actLeft'
      ShortCut = 37
      OnExecute = actMoveExecute
    end
    object actRight: TAction
      Tag = 3
      Caption = 'actRight'
      ShortCut = 39
      OnExecute = actMoveExecute
    end
    object actRotate: TAction
      Caption = 'actRotate'
      ShortCut = 32
      OnExecute = actMoveExecute
    end
    object actLRotate: TAction
      Caption = 'actLRotate'
      ShortCut = 8224
      OnExecute = actMoveExecute
    end
    object actPause: TAction
      Caption = 'actPause'
      ShortCut = 80
      OnExecute = actPauseExecute
    end
    object actSave: TAction
      Caption = 'actSave'
      ShortCut = 16467
      OnExecute = actSaveExecute
    end
    object actLoad: TAction
      Caption = 'actLoad'
      ShortCut = 16463
      OnExecute = actLoadExecute
    end
    object actClearStat: TAction
      Caption = 'actClearStat'
      ShortCut = 32851
      OnExecute = actClearStatExecute
    end
  end
  object Timer: TTimer
    Enabled = False
    Interval = 500
    OnTimer = TimerTimer
    Left = 40
    Top = 4
  end
  object Time: TTimer
    Interval = 10000
    OnTimer = TimeTimer
    Left = 76
    Top = 4
  end
end
