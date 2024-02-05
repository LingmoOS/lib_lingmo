pkgname="liblinmo"
pkgver="2.0.0"
pkgrel="1"
pkgdesc="LingmoOS & LingmoDE Library"
arch=("x86_64")
depends=('kscreen' 'modemmanager-qt5' 'networkmanager-qt5' 'qt5-quickcontrols2' 'accountsservice' 'bluez' 'bluez-qt5')
makedepends=('extra-cmake-modules' 'ninja' 'qt5-tools' 'git')
provides=("$pkgname")
conflicts=("$pkgname")
source=(".")
license=("GPL2.0")
sha512sums=("SKIP")

build() {
	cmake -GNinja -DCMAKE_INSTALL_PREFIX=/usr .
	ninja
}

package() {
	DESTDIR="$pkgdir" ninja install
}
