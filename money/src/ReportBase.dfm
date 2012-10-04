object fmReportBase: TfmReportBase
  Left = 774
  Top = 317
  Width = 670
  Height = 749
  Caption = 'fmReportBase'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnDestroy = FormDestroy
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 13
  object pnlFilter: TPanel
    Left = 0
    Top = 0
    Width = 662
    Height = 29
    Align = alTop
    TabOrder = 0
    object pnlDateInterval: TPanel
      Left = 1
      Top = 1
      Width = 252
      Height = 27
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 0
      object lDateInterval: TLabel
        Left = 8
        Top = 6
        Width = 60
        Height = 13
        Cursor = crHandPoint
        Caption = 'lDateInterval'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -10
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        OnClick = lDateIntervalClick
        OnMouseEnter = lMouseEnter
        OnMouseLeave = lMouseLeave
      end
    end
    object pnlDateIntervalType: TPanel
      Left = 253
      Top = 1
      Width = 252
      Height = 27
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 1
      object lDateIntervalType: TLabel
        Left = 8
        Top = 6
        Width = 84
        Height = 13
        Cursor = crHandPoint
        Caption = 'lDateIntervalType'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -10
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        OnClick = lDateIntervalTypeClick
        OnMouseEnter = lMouseEnter
        OnMouseLeave = lMouseLeave
      end
    end
  end
  object pnlMain: TPanel
    Left = 0
    Top = 29
    Width = 662
    Height = 690
    Align = alClient
    TabOrder = 1
  end
  object alMain: TActionList
    Left = 16
    Top = 40
    object actClose: TAction
      Caption = 'actClose'
      ShortCut = 8219
      OnExecute = actCloseExecute
    end
    object actChangeDateInterval: TAction
      Caption = 'actChangeDateInterval'
      OnExecute = actChangeDateIntervalExecute
    end
    object actRunReport: TAction
      Caption = 'actRunReport'
      OnExecute = actRunReportExecute
    end
    object actChangeDateIntervalType: TAction
      Caption = 'actChangeDateIntervalType'
      OnExecute = actChangeDateIntervalTypeExecute
    end
  end
end
