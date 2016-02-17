//
//  ViewController.swift
//  TransmitWeaver
//
//  Created by Stephen Radford on 16/02/2016.
//  Copyright © 2016 Cocoon Development Ltd. All rights reserved.
//

import Cocoa
import AEXML

class ViewController: NSViewController, DropzoneDelegate {

    @IBOutlet weak var dropZone: DropzoneView!
    
    @IBOutlet weak var dropBG: NSImageView!
    
    @IBOutlet weak var dropLabel: NSTextField!
    
    let offImage = NSImage(named: "dropzone")
    
    let onImage = NSImage(named: "dropzone-active")
    
    // After Decode Stuff
    
    @IBOutlet weak var postDecode: NSView!
    
    @IBOutlet weak var hostTextField: NSTextField!
    
    @IBOutlet weak var pathField: NSTextField!
    
    @IBOutlet weak var usernameField: NSTextField!
    
    @IBOutlet weak var passwordField: NSTextField!
    
    @IBOutlet weak var protocolField: NSTextField!
    
    @IBOutlet weak var transmitBtn: NSButton!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        postDecode.hidden = true
        
        view.wantsLayer = true
        view.layer?.backgroundColor = NSColor.whiteColor().CGColor
        
        dropZone.delegate = self
        
        if(!checkForTransmit()) {
            transmitBtn.hidden = true
        }
        
    }
    
    func parseSTEFile(data: NSData) {
        do {
            let doc = try AEXMLDocument(xmlData: data)
            if let server = doc.root["serverlist"]["server"].all?[0] {
                if let encodedPassword = server.attributes["pw"],host = server.attributes["host"], user = server.attributes["user"], path = server.attributes["remoteroot"], sftp = server.attributes["useSFTP"], ftps = server.attributes["useFTPS"]  {
                    
                    dropZone.hidden = true
                    dropBG.hidden = true
                    dropLabel.hidden = true
                    postDecode.hidden = false
                    
                    let password = encodedPassword.decodePassword()
                    hostTextField.stringValue = host
                    passwordField.stringValue = password
                    usernameField.stringValue = user
                    pathField.stringValue = path

                    if sftp == "TRUE" {
                        protocolField.stringValue = "SFTP"
                    } else if ftps == "TRUE" {
                        protocolField.stringValue = "FTPS"
                    } else {
                        protocolField.stringValue = "FTP "
                    }
                    
                }
            }
        } catch {
            Swift.print("Could not parse XML")
        }
    }
    
    
    // MARK: - Transmit
    
    @IBAction func openInTransmit(sender: AnyObject) {
        
        let baseURL = NSBundle.mainBundle().URLForResource("baseScript", withExtension: "txt")
        if let path = baseURL?.path {
            do {
                let baseScript = try String(contentsOfFile: path)
                let replaced = baseScript
                    .stringByReplacingOccurrencesOfString("{{HOST}}", withString: hostTextField.stringValue)
                    .stringByReplacingOccurrencesOfString("{{USERNAME}}", withString: usernameField.stringValue)
                    .stringByReplacingOccurrencesOfString("{{PASSWORD}}", withString: passwordField.stringValue)
                    .stringByReplacingOccurrencesOfString("{{PATH}}", withString: pathField.stringValue)
                    .stringByReplacingOccurrencesOfString("{{PROTOCOL}}", withString: protocolField.stringValue)
                
                let script = NSAppleScript(source: replaced)
                var errorPointer: NSDictionary?
                script?.executeAndReturnError(&errorPointer)
                
            } catch {
                Swift.print("Could not open base script")
            }
        }
        
    }
    
    func checkForTransmit() -> Bool {
        if NSWorkspace.sharedWorkspace().absolutePathForAppBundleWithIdentifier("com.panic.Transmit") != nil {
            return true
        }
        return false
    }
    
    

    // MARK: - DropzoneDelegate
    
    func dragStart() {
        dropBG.image = onImage
        dropLabel.stringValue = "Drop To Decode"
    }
    
    func dragEnd() {
        dropBG.image = offImage
        dropLabel.stringValue = "Drag .STE Here"
    }
    
    func dragCompleted(path: String) {
        if let data = NSData(contentsOfFile: path) {
            parseSTEFile(data)
        }
    }

}

