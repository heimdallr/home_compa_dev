object fmIndicator: TfmIndicator
  Left = 557
  Top = 126
  Width = 187
  Height = 400
  Caption = 'fmIndicator'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object pnlRight: TPanel
    Left = 0
    Top = 0
    Width = 179
    Height = 376
    Align = alClient
    TabOrder = 0
    object pnlInfo: TPanel
      Left = 1
      Top = 157
      Width = 177
      Height = 218
      Align = alClient
      TabOrder = 0
      DesignSize = (
        177
        218)
      object eCount: TLabeledEdit
        Left = 16
        Top = 24
        Width = 145
        Height = 21
        TabStop = False
        Anchors = [akLeft, akTop, akRight]
        BiDiMode = bdLeftToRight
        EditLabel.Width = 23
        EditLabel.Height = 13
        EditLabel.BiDiMode = bdLeftToRight
        EditLabel.Caption = #1057#1095#1077#1090
        EditLabel.ParentBiDiMode = False
        LabelPosition = lpAbove
        LabelSpacing = 1
        ParentBiDiMode = False
        ReadOnly = True
        TabOrder = 0
        Text = '0'
      end
      object eLine: TLabeledEdit
        Left = 16
        Top = 66
        Width = 145
        Height = 21
        TabStop = False
        Anchors = [akLeft, akTop, akRight]
        EditLabel.Width = 32
        EditLabel.Height = 13
        EditLabel.Caption = #1051#1080#1085#1080#1080
        LabelPosition = lpAbove
        LabelSpacing = 1
        ReadOnly = True
        TabOrder = 1
      end
      object eFig: TLabeledEdit
        Left = 17
        Top = 108
        Width = 145
        Height = 21
        TabStop = False
        Anchors = [akLeft, akTop, akRight]
        BiDiMode = bdLeftToRight
        EditLabel.Width = 39
        EditLabel.Height = 13
        EditLabel.BiDiMode = bdLeftToRight
        EditLabel.Caption = #1060#1080#1075#1091#1088#1072
        EditLabel.ParentBiDiMode = False
        LabelPosition = lpAbove
        LabelSpacing = 1
        ParentBiDiMode = False
        ReadOnly = True
        TabOrder = 2
      end
      object eFig0: TLabeledEdit
        Left = 17
        Top = 150
        Width = 145
        Height = 21
        TabStop = False
        Anchors = [akLeft, akTop, akRight]
        EditLabel.Width = 98
        EditLabel.Height = 13
        EditLabel.Caption = #1057#1083#1077#1076#1091#1102#1097#1072#1103' '#1092#1080#1075#1091#1088#1072
        LabelPosition = lpAbove
        LabelSpacing = 1
        ReadOnly = True
        TabOrder = 3
      end
    end
    object pnlImgNext: TPanel
      Left = 1
      Top = 1
      Width = 177
      Height = 156
      Align = alTop
      TabOrder = 1
      object imNext: TImage
        Left = 1
        Top = 1
        Width = 175
        Height = 154
        Align = alClient
      end
    end
  end
end
