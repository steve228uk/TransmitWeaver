/*
 * Transmit.h
 */

#import <AppKit/AppKit.h>
#import <ScriptingBridge/ScriptingBridge.h>


@class TransmitApplication, TransmitDocument, TransmitWindow, TransmitDocument, TransmitTab, TransmitFileBrowser, TransmitFavorite, TransmitSkipRule, TransmitBrowserItem, TransmitSelectedBrowserItem;

enum TransmitSaveOptions {
	TransmitSaveOptionsYes = 'yes ' /* Save the file. */,
	TransmitSaveOptionsNo = 'no  ' /* Do not save the file. */,
	TransmitSaveOptionsAsk = 'ask ' /* Ask the user whether or not to save the file. */
};
typedef enum TransmitSaveOptions TransmitSaveOptions;

enum TransmitPrintingErrorHandling {
	TransmitPrintingErrorHandlingStandard = 'lwst' /* Standard PostScript error handling */,
	TransmitPrintingErrorHandlingDetailed = 'lwdt' /* print a detailed report of PostScript errors */
};
typedef enum TransmitPrintingErrorHandling TransmitPrintingErrorHandling;

enum TransmitSaveableFileFormat {
	TransmitSaveableFileFormatText = 'txt ' /* Text Document Format */
};
typedef enum TransmitSaveableFileFormat TransmitSaveableFileFormat;

enum TransmitConnectprotocol {
	TransmitConnectprotocolFTP = 'FTP ' /* FTP Protocol */,
	TransmitConnectprotocolFTPImplicitSSL = 'FSSL' /* FTP with implicit SLL */,
	TransmitConnectprotocolFTPTLSSSL = 'FTPS' /* FTP with TLS/SSL */,
	TransmitConnectprotocolS3 = 'S3  ' /* Amazon S3 */,
	TransmitConnectprotocolSFTP = 'SFTP' /* SFTP */,
	TransmitConnectprotocolWebDAV = 'WDAV' /* WebDAV */,
	TransmitConnectprotocolWebDAVHTTPS = 'SDAV' /* WebDAV with HTTPS */
};
typedef enum TransmitConnectprotocol TransmitConnectprotocol;

enum TransmitResumetype {
	TransmitResumetypeAsk = 'aTRN' /* Ask how to proceed if a duplicate file exists. */,
	TransmitResumetypeOverwrite = 'oTRN' /* Overwrite a duplicate file. */,
	TransmitResumetypeResume = 'rTRN' /* Try and continue transferring a duplicate file. */,
	TransmitResumetypeSkip = 'sTRN' /* Skip a duplicate file. */
};
typedef enum TransmitResumetype TransmitResumetype;

enum TransmitItemtype {
	TransmitItemtypeFolderItem = 'FKfo' /* Browser item folders. */,
	TransmitItemtypeFileItem = 'FKfi' /* Browser item files. */,
	TransmitItemtypeAliasItem = 'FKal' /* Browser item aliases. */,
	TransmitItemtypeSmartFolderItem = 'FKsm' /* Browser item smart folders. */
};
typedef enum TransmitItemtype TransmitItemtype;

@protocol TransmitGenericMethods

- (void) closeSaving:(TransmitSaveOptions)saving savingIn:(NSURL *)savingIn;  // Close a document.
- (void) saveIn:(NSURL *)in_ as:(TransmitSaveableFileFormat)as;  // Save a document.
- (void) printWithProperties:(NSDictionary *)withProperties printDialog:(BOOL)printDialog;  // Print a document.
- (void) delete;  // Delete an object.
- (void) duplicateTo:(SBObject *)to withProperties:(NSDictionary *)withProperties;  // Copy an object.
- (void) moveTo:(SBObject *)to;  // Move an object to a new location.

@end



/*
 * Standard Suite
 */

// The application's top-level scripting object.
@interface TransmitApplication : SBApplication

- (SBElementArray<TransmitDocument *> *) documents;
- (SBElementArray<TransmitWindow *> *) windows;

@property (copy, readonly) NSString *name;  // The name of the application.
@property (readonly) BOOL frontmost;  // Is this the active application?
@property (copy, readonly) NSString *version;  // The version number of the application.

- (id) open:(id)x;  // Open a document.
- (void) print:(id)x withProperties:(NSDictionary *)withProperties printDialog:(BOOL)printDialog;  // Print a document.
- (void) quitSaving:(TransmitSaveOptions)saving;  // Quit the application.
- (BOOL) exists:(id)x;  // Verify that an object exists.
- (void) getURL:(NSString *)x;  // Open a selected URL from a different application.
- (void) openURL:(NSString *)x;  // Open a selected URL from a different application.

@end

// A document.
@interface TransmitDocument : SBObject <TransmitGenericMethods>

@property (copy, readonly) NSString *name;  // Its name.
@property (readonly) BOOL modified;  // Has it been modified since the last save?
@property (copy, readonly) NSURL *file;  // Its location on disk, if it has one.


@end

// A window.
@interface TransmitWindow : SBObject <TransmitGenericMethods>

@property (copy, readonly) NSString *name;  // The title of the window.
- (NSInteger) id;  // The unique identifier of the window.
@property NSInteger index;  // The index of the window, ordered front to back.
@property NSRect bounds;  // The bounding rectangle of the window.
@property (readonly) BOOL closeable;  // Does the window have a close button?
@property (readonly) BOOL miniaturizable;  // Does the window have a minimize button?
@property BOOL miniaturized;  // Is the window minimized right now?
@property (readonly) BOOL resizable;  // Can the window be resized?
@property BOOL visible;  // Is the window visible right now?
@property (readonly) BOOL zoomable;  // Does the window have a zoom button?
@property BOOL zoomed;  // Is the window zoomed right now?
@property (copy, readonly) TransmitDocument *document;  // The document whose contents are displayed in the window.


@end



/*
 * Transmit Suite
 */

// Transmit's top level scripting object.
@interface TransmitApplication (TransmitSuite)

- (SBElementArray<TransmitFavorite *> *) favorites;
- (SBElementArray<TransmitSkipRule *> *) skipRules;

@property BOOL suppressErrors;  // Do not show error dialogs during AppleScript execution (on by default).

@end

// A Transmit document.
@interface TransmitDocument (TransmitSuite)

- (SBElementArray<TransmitTab *> *) tabs;

@property (copy) TransmitTab *currentTab;  // The currently visible tab in the document.

@end

// A tab in Transmit.
@interface TransmitTab : SBObject <TransmitGenericMethods>

- (SBElementArray<TransmitFileBrowser *> *) fileBrowsers;

@property (copy, readonly) NSString *name;  // The current name of the tab.
@property (copy, readonly) TransmitFileBrowser *localBrowser;  // The active local file browser if available.
@property (copy, readonly) TransmitFileBrowser *remoteBrowser;  // The active remote file browser if available.
@property (copy, readonly) TransmitFileBrowser *leftBrowser;  // The left file browser if available.
@property (copy, readonly) TransmitFileBrowser *rightBrowser;  // The right file browser if available.

- (BOOL) connectTo:(TransmitFavorite *)to toAddress:(NSString *)toAddress asUser:(NSString *)asUser usingPort:(NSInteger)usingPort withInitialPath:(NSString *)withInitialPath withPassword:(NSString *)withPassword withProtocol:(TransmitConnectprotocol)withProtocol mount:(BOOL)mount;  // Connect to a favorite or a specified server.

@end

// A file browser in Transmit.
@interface TransmitFileBrowser : SBObject <TransmitGenericMethods>

- (SBElementArray<TransmitBrowserItem *> *) browserItems;
- (SBElementArray<TransmitSelectedBrowserItem *> *) selectedBrowserItems;

@property (copy, readonly) NSString *rootPath;  // The current file browser path.
@property (readonly) BOOL remote;  // Whether the file browser is listing remote files.
@property BOOL showHidden;  // Whether the file browser is showing invisible files.
@property (copy, readonly) TransmitFavorite *favorite;  // The favorite the file browser is associated with (if applicable).
@property (copy, readonly) NSString *address;  // The server address the file browser is associated with (if applicable).
@property (copy, readonly) NSString *username;  // The server user name the file browser is associated with (if applicable).

- (BOOL) changeLocationToPath:(NSString *)toPath;  // Change the current location of the file browser.
- (BOOL) createFolderNamed:(NSString *)named;  // Create a new folder.
- (BOOL) createFileNamed:(NSString *)named;  // Create a new file.
- (void) refresh;  // Refresh the file list.
- (BOOL) synchronizeTo:(TransmitFileBrowser *)to deleteOrphanedItems:(BOOL)deleteOrphanedItems compareUsingSize:(BOOL)compareUsingSize followSymlinks:(BOOL)followSymlinks automaticallyDetermineTimeOffset:(BOOL)automaticallyDetermineTimeOffset withTimeOffset:(NSInteger)withTimeOffset usingSkipRules:(NSArray<TransmitSkipRule *> *)usingSkipRules saveReportToPath:(NSString *)saveReportToPath;  // Update files located on the destination with files located on the source.
- (BOOL) renameItemAtPath:(NSString *)itemAtPath to:(NSString *)to;  // Rename a file at a path.
- (BOOL) downloadItemAtPath:(NSString *)itemAtPath to:(NSString *)to withResumeMode:(TransmitResumetype)withResumeMode continueAfterError:(BOOL)continueAfterError usingSkipRules:(NSArray<TransmitSkipRule *> *)usingSkipRules;  // Download a file at a path.
- (BOOL) uploadItemAtPath:(NSString *)itemAtPath to:(NSString *)to withResumeMode:(TransmitResumetype)withResumeMode continueAfterError:(BOOL)continueAfterError usingSkipRules:(NSArray<TransmitSkipRule *> *)usingSkipRules;  // Upload a file at a path.
- (BOOL) deleteItemAtPath:(NSString *)atPath;  // Delete a file at a path.

@end

// A favorite in Transmit.
@interface TransmitFavorite : SBObject <TransmitGenericMethods>

@property (copy, readonly) NSString *address;  // The address of the favorite.
@property (copy, readonly) NSString *localPath;  // The local path for the favorite.
@property (copy, readonly) NSString *password;  // The password for a favorite.
@property (readonly) NSInteger port;  // The port to connect to for a favorite.
@property (readonly) TransmitConnectprotocol protocol;  // The protocol a favorite uses to connect.
@property (copy, readonly) NSString *remotePath;  // The remote path for a favorite.
@property (copy, readonly) NSString *name;  // The name of a favorite.
@property (copy, readonly) NSString *URL;  // The root URL specified for a favorite.
@property (copy, readonly) NSString *userName;  // The user name for a favorite.
@property (copy, readonly) NSString *identifier;  // The unique identifier for a favorite.


@end

// A Transmit Skip Rule.
@interface TransmitSkipRule : SBObject <TransmitGenericMethods>

@property (copy, readonly) NSString *name;  // The name of the skip rule.
@property (readonly) BOOL enabled;  // Is the skip rule currently enabled in Transmit.
@property (copy, readonly) NSString *identifier;  // The unique identifier of the rule.


@end

// A file, folder or alias.
@interface TransmitBrowserItem : SBObject <TransmitGenericMethods>

@property (copy, readonly) NSString *name;  // The name of the browser item.
@property (copy, readonly) NSString *displayName;  // The display name of the browser item.
@property (copy, readonly) NSString *path;  // The path of the browser item.
@property (readonly) NSInteger size;  // The logical size of the browser item.
@property (readonly) NSInteger physicalSize;  // The actual space used on disk of the browser item.
@property (copy, readonly) NSDate *creationDate;  // The date on which the browser item was created.
@property (copy, readonly) NSDate *modificationDate;  // The date on which the browser item was last modified.
@property (readonly) TransmitItemtype itemType;  // The type of the browser item.


@end

// A file, folder or alias.
@interface TransmitSelectedBrowserItem : TransmitBrowserItem


@end

